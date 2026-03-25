#include "kbus.h"
#include "ring_buf.h"

typedef struct
{
    void (*on_recv)(const kbus_frame_t *frame);
    void (*on_send)(const kbus_frame_t *frame);
} kbus_handle_t;

static QueueHandle_t uart_queue;

static kbus_handle_t kbus_handle = {0};
static kbus_config_t kbus_config = {0};

static ring_buf_t rb;

static bool kbus_parse(const uint8_t *buf, uint16_t buf_len, kbus_frame_t *frame);
static uint8_t kbus_calculate_crc(const uint8_t *buf, uint16_t len);
static void uart_task(void *args);

esp_err_t kbus_init(kbus_config_t *config)
{
    kbus_config = *config;

    ring_buf_init(&rb);

    uart_config_t uart_config = {
        .baud_rate = 9600,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_EVEN,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
    };
    uart_param_config(kbus_config.uart_num, &uart_config);
    uart_set_pin(kbus_config.uart_num, kbus_config.uart_tx_io, kbus_config.uart_rx_io, GPIO_NUM_NC, GPIO_NUM_NC);
    // uart_set_rx_timeout(kbus_config.uart_num, 10);
    uart_driver_install(kbus_config.uart_num, kbus_config.rx_buf_size, kbus_config.tx_buf_size, kbus_config.queue_size, &uart_queue, 0);

    xTaskCreate(uart_task, "uart_task", 4096, NULL, 5, NULL);

    return ESP_OK;
}

esp_err_t kbus_register_recv_cb(kbus_recv_cb_t cb)
{
    kbus_handle.on_recv = (kbus_recv_cb_t)cb;

    return ESP_OK;
}

esp_err_t kbus_register_send_cb(kbus_send_cb_t cb)
{
    kbus_handle.on_send = (kbus_send_cb_t)cb;

    return ESP_OK;
}

static bool kbus_parse(const uint8_t *buf, uint16_t buf_len, kbus_frame_t *frame)
{
    if (buf == NULL || frame == NULL)
    {
        return false;
    }

    if (buf_len < 2)
    {
        ESP_LOGW("KBUS", "Buffer too short: %d bytes", buf_len);
        return false;
    }

    // Parse K-Bus frame structure:
    // Byte 0: SRC
    // Byte 1: LEN (DST + CMD + DATA + CRC)
    // Bytes 2 to (2+LEN-1): DST, CMD, DATA, CRC

    uint8_t src = buf[0];
    uint8_t len = buf[1];

    if (len < 3)
    {
        ESP_LOGW("KBUS", "LEN too small: %d", len);
        return false;
    }

    uint16_t frame_total = 2u + len;

    if (buf_len < frame_total)
    {
        ESP_LOGW("KBUS", "Incomplete frame: got %d, need %d", buf_len, frame_total);
        return false;
    }

    uint8_t dst = buf[2];
    uint8_t cmd = buf[3];
    uint8_t data_len = len - 3;
    uint8_t crc_rx = buf[frame_total - 1];

    if (data_len > 253)
    {
        ESP_LOGE("KBUS", "Data_len overflow: %d", data_len);
        return false;
    }

    // Calculate CRC for entire frame except CRC itself
    // CRC = XOR of all bytes: SRC + LEN + DST + CMD + DATA
    uint8_t crc_calc = kbus_calculate_crc(buf, frame_total - 1);

    if (crc_calc != crc_rx)
    {
        ESP_LOGW("KBUS", "CRC mismatch: calc=0x%02X recv=0x%02X", crc_calc, crc_rx);
        return false;
    }

    frame->src = src;
    frame->len = len;
    frame->dst = dst;
    frame->cmd = cmd;
    frame->data_len = data_len;
    frame->crc = crc_rx;

    if (data_len > 0)
    {
        memcpy(frame->data, &buf[4], data_len);
    }

    return true;
}

static uint8_t kbus_calculate_crc(const uint8_t *buf, uint16_t len)
{
    uint8_t crc = 0;
    for (uint16_t i = 0; i < len; i++)
    {
        crc ^= buf[i];
    }
    return crc;
}

static void uart_task(void *args)
{
    uart_event_t event;
    uint8_t *dtmp = (uint8_t *)malloc(kbus_config.rx_buf_size);
    assert(dtmp);

    while (1)
    {
        if (xQueueReceive(uart_queue, &event, portMAX_DELAY))
        {
            bzero(dtmp, kbus_config.rx_buf_size);
            switch (event.type)
            {
            case UART_DATA:
                uart_read_bytes(kbus_config.uart_num, dtmp, event.size, portMAX_DELAY);

                for (int i = 0; i < event.size; i++)
                {
                    ring_buf_push(&rb, dtmp[i]);
                }

                while (ring_buf_size(&rb) >= 5)
                {
                    uint8_t src, len;
                    ring_buf_peek(&rb, 0, &src);
                    ring_buf_peek(&rb, 1, &len);

                    if (len < 3)
                    {
                        ring_buf_pop(&rb, NULL);
                        continue;
                    }

                    size_t frame_total = 2 + len;
                    if (ring_buf_size(&rb) < frame_total)
                    {
                        break;
                    }

                    uint8_t frame_buf[258];
                    ring_buf_read(&rb, frame_buf, frame_total);

                    kbus_frame_t frame;
                    if (kbus_parse(frame_buf, frame_total, &frame))
                    {
                        if (kbus_handle.on_recv != NULL)
                        {
                            kbus_handle.on_recv(&frame);
                        }
                    }
                }
                break;
            case UART_FIFO_OVF:
                ESP_LOGI("UART", "Fifo overflow");
                uart_flush_input(UART_NUM_1);
                xQueueReset(uart_queue);
                break;
            case UART_BUFFER_FULL:
                ESP_LOGI("UART", "Ring buffer full");
                uart_flush_input(UART_NUM_1);
                xQueueReset(uart_queue);
                break;
            case UART_BREAK:
                ESP_LOGI("UART", "RX break detect");
                uart_flush_input(UART_NUM_1);
                xQueueReset(uart_queue);
                break;
            case UART_PARITY_ERR:
                ESP_LOGI("UART", "Parity error");
                break;
            case UART_FRAME_ERR:
                ESP_LOGI("UART", "Frame error");
                break;
            default:
                ESP_LOGI("UART", "Event type: %d", event.type);
                break;
            }
        }
    }
    free(dtmp);
    dtmp = NULL;
    vTaskDelete(NULL);
}

esp_err_t kbus_send(uint8_t src, uint8_t dst, uint8_t cmd, const uint8_t *data, uint8_t data_len)
{
    // Validate data length (max 253 bytes of data)
    if (data_len > 253)
    {
        ESP_LOGE("KBUS", "Data length too long: %d", data_len);
        return ESP_ERR_INVALID_ARG;
    }

    // Validate pointers
    if (data == NULL && data_len > 0)
    {
        ESP_LOGE("KBUS", "Data pointer is NULL but data_len > 0");
        return ESP_ERR_INVALID_ARG;
    }

    // Calculate frame structure:
    // Byte 0: SRC
    // Byte 1: LEN (DST + CMD + DATA + CRC)
    // Byte 2: DST
    // Byte 3: CMD
    // Bytes 4 to 4+data_len-1: data
    // Last byte: CRC

    uint8_t len = 3 + data_len; // LEN = DST + CMD + CRC + DATA
    uint8_t frame_buf[258];
    uint8_t frame_size = 2 + len; // SRC + LEN + (DST + CMD + DATA + CRC)

    frame_buf[0] = src;
    frame_buf[1] = len;
    frame_buf[2] = dst;
    frame_buf[3] = cmd;

    // Copy data if present
    if (data_len > 0)
    {
        memcpy(&frame_buf[4], data, data_len);
    }

    // Calculate CRC for entire frame except CRC itself
    // CRC = XOR of all bytes: SRC + LEN + DST + CMD + DATA
    uint8_t crc = kbus_calculate_crc(frame_buf, 2 + len - 1);
    frame_buf[frame_size - 1] = crc;

    // Send via UART
    uart_write_bytes(kbus_config.uart_num, (const char *)frame_buf, frame_size);

    // Create frame structure for callback
    kbus_frame_t sent_frame;
    sent_frame.src = src;
    sent_frame.len = len;
    sent_frame.dst = dst;
    sent_frame.cmd = cmd;
    sent_frame.crc = crc;
    sent_frame.data_len = data_len;
    if (data_len > 0)
    {
        memcpy(sent_frame.data, data, data_len);
    }

    // Call send callback if registered
    if (kbus_handle.on_send != NULL)
    {
        kbus_handle.on_send(&sent_frame);
    }

    return ESP_OK;
}

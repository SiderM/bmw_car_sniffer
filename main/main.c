#include "display.h"
#include "kbus.h"
#include "can.h"
#include "ui.h"

static void kbus_on_recv(const kbus_frame_t *frame)
{
    ESP_LOGI("KBUS_RX", "SRC: 0x%02X LEN: 0x%02X DST: 0x%02X CMD: 0x%02X CRC: 0x%02X", frame->src, frame->len, frame->dst, frame->cmd, frame->crc);
    ESP_LOG_BUFFER_HEX("KBUS_RX", frame->data, frame->data_len);
    if (frame->cmd == 0x5C)
    {
        display_brightness_set(frame->data[0]);
    }
}

static void can_on_recv(const can_frame_t *frame)
{
    ESP_LOGI("CAN_RX", "ID: 0x%03X", frame->id);
    ESP_LOG_BUFFER_HEX("CAN_RX", frame->data, frame->data_len);
}

void app_main(void)
{
    kbus_config_t kbus_config = {
        .uart_num = UART_NUM_1,
        .uart_rx_io = GPIO_NUM_21,
        .uart_tx_io = GPIO_NUM_22,
        .rx_buf_size = 2048,
        .tx_buf_size = 1024,
        .queue_size = 32,
    };
    kbus_init(&kbus_config);
    kbus_register_recv_cb(kbus_on_recv);

    can_config_t can_config = {
        .twai_rx_io = GPIO_NUM_6,
        .twai_tx_io = GPIO_NUM_5,
        .bitrate = 500000,
    };
    can_init(&can_config);
    can_register_recv_cb(can_on_recv);

    display_init();
    esp_lv_adapter_lock(-1);
    ui_init();
    esp_lv_adapter_unlock();
}

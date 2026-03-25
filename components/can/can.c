#include "can.h"

typedef struct
{
    void (*on_recv)(const can_frame_t *frame);
} can_handle_t;

static QueueHandle_t twai_queue;

static can_handle_t can_handle = {0};
static can_config_t can_config = {0};

static bool twai_rx_callback(twai_node_handle_t handle, const twai_rx_done_event_data_t *edata, void *user_ctx);
static void twai_task(void *args);

void can_init(can_config_t *config)
{
    can_config = *config;

    twai_onchip_node_config_t twai_onchip_node_config = {
        .io_cfg = {
            .tx = can_config.twai_tx_io,
            .rx = can_config.twai_rx_io,
        },
        .bit_timing.bitrate = can_config.bitrate,
        .tx_queue_depth = 10,
        .flags = {
            .no_receive_rtr = true,
        },
    };
    twai_node_handle_t twai_node_handle;
    twai_new_node_onchip(&twai_onchip_node_config, &twai_node_handle);

    twai_mask_filter_config_t twai_mask_filter_config = {
        .id = 0,
        .mask = 0,
        .is_ext = 0,
    };
    twai_node_config_mask_filter(twai_node_handle, 0, &twai_mask_filter_config);

    twai_event_callbacks_t twai_event_callbacks = {
        .on_rx_done = twai_rx_callback,
    };
    twai_node_register_event_callbacks(twai_node_handle, &twai_event_callbacks, NULL);
    twai_node_enable(twai_node_handle);

    twai_queue = xQueueCreate(40, sizeof(can_frame_t));
    xTaskCreate(twai_task, "twai_task", 4096, NULL, 5, NULL);
}

void can_register_recv_cb(can_recv_cb_t cb)
{
    can_handle.on_recv = (can_recv_cb_t)cb;
}

static bool twai_rx_callback(twai_node_handle_t handle, const twai_rx_done_event_data_t *edata, void *user_ctx)
{
    twai_frame_t twai_rx_frame = {0};
    uint8_t rx_buffer[8];
    twai_rx_frame.buffer = rx_buffer;
    twai_rx_frame.buffer_len = sizeof(rx_buffer);

    if (twai_node_receive_from_isr(handle, &twai_rx_frame) == ESP_OK)
    {
        can_frame_t frame = {
            .id = twai_rx_frame.header.id,
            .data_len = twai_rx_frame.header.dlc,
        };
        memcpy(frame.data, rx_buffer, twai_rx_frame.header.dlc);

        xQueueSendFromISR(twai_queue, &frame, NULL);
    }

    return false;
}

static void twai_task(void *args)
{
    can_frame_t frame;

    while (1)
    {
        if (xQueueReceive(twai_queue, &frame, portMAX_DELAY))
        {
            if (can_handle.on_recv != NULL)
            {
                can_handle.on_recv(&frame);
            }
        }
    }
    vTaskDelete(NULL);
}

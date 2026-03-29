#ifndef CAN_H
#define CAN_H

#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "esp_twai.h"
#include "esp_twai_onchip.h"
#include "can_defs.h"

typedef struct
{
    uint32_t id;
    uint8_t data[8];
    uint8_t data_len;
} can_frame_t;

typedef struct
{
    gpio_num_t twai_rx_io;
    gpio_num_t twai_tx_io;
    uint32_t bitrate;
} can_config_t;

typedef void (*can_recv_cb_t)(const can_frame_t *frame);

void can_init(can_config_t *config);
void can_register_recv_cb(can_recv_cb_t cb);

#endif // CAN_H

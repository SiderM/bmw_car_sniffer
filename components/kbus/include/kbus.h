#ifndef KBUS_H
#define KBUS_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "driver/uart.h"
#include "esp_err.h"
#include "esp_log.h"

typedef struct
{
    uint8_t src;
    uint8_t len;
    uint8_t dst;
    uint8_t cmd;
    uint8_t crc;
    uint8_t data[253];
    uint8_t data_len;
} kbus_frame_t;

typedef struct
{
    uart_port_t uart_num;
    gpio_num_t uart_rx_io;
    gpio_num_t uart_tx_io;
    int rx_buf_size;
    int tx_buf_size;
    int queue_size;
} kbus_config_t;

typedef void (*kbus_recv_cb_t)(const kbus_frame_t *frame);
typedef void (*kbus_send_cb_t)(const kbus_frame_t *frame);

esp_err_t kbus_init(kbus_config_t *config);
esp_err_t kbus_register_recv_cb(kbus_recv_cb_t cb);
esp_err_t kbus_register_send_cb(kbus_send_cb_t cb);
esp_err_t kbus_send(uint8_t src, uint8_t dst, uint8_t cmd, const uint8_t *data, uint8_t data_len);

#endif // ESP_KBUS_H

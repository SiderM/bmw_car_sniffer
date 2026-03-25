#ifndef DISPLAY_H
#define DISPLAY_H

#include "driver/gpio.h"
#include "driver/i2c_master.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_mipi_dsi.h"
#include "esp_ldo_regulator.h"
#include "esp_lcd_jd9365.h"
#include "esp_lcd_touch_gt911.h"
#include "esp_lv_adapter.h"

void display_init(void);
void display_brightness_set(uint8_t brightness);

#endif // BSP_DISPLAY_H

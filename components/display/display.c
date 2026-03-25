#include "display.h"

static i2c_master_bus_handle_t i2c_master_bus_handle;
static esp_lcd_panel_io_handle_t esp_lcd_panel_io_handle;
static esp_lcd_panel_handle_t esp_lcd_panel_handle;
static esp_lcd_touch_handle_t esp_lcd_touch_handle;

static void display_panel_init(void);
static void display_touch_init(void);

void display_init(void)
{
    i2c_master_bus_config_t i2c_master_bus_config = {
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .sda_io_num = GPIO_NUM_7,
        .scl_io_num = GPIO_NUM_8,
        .i2c_port = I2C_NUM_1,
    };
    i2c_new_master_bus(&i2c_master_bus_config, &i2c_master_bus_handle);

    display_panel_init();
    display_touch_init();

    esp_lv_adapter_config_t esp_lv_adapter_config = ESP_LV_ADAPTER_DEFAULT_CONFIG();
    esp_lv_adapter_init(&esp_lv_adapter_config);

    esp_lv_adapter_display_config_t esp_lv_adapter_display_config = ESP_LV_ADAPTER_DISPLAY_MIPI_DEFAULT_CONFIG(esp_lcd_panel_handle, esp_lcd_panel_io_handle, 800, 1280, ESP_LV_ADAPTER_ROTATE_0);
    lv_display_t *display = esp_lv_adapter_register_display(&esp_lv_adapter_display_config);

    esp_lv_adapter_touch_config_t esp_lv_adapter_touch_config = ESP_LV_ADAPTER_TOUCH_DEFAULT_CONFIG(display, esp_lcd_touch_handle);
    esp_lv_adapter_register_touch(&esp_lv_adapter_touch_config);

    esp_lv_adapter_start();
}

void display_brightness_set(uint8_t brightness)
{
    i2c_device_config_t i2c_device_config = {
        .scl_speed_hz = 100000,
        .device_address = 0x45,
    };
    i2c_master_dev_handle_t i2c_master_dev_handle;
    i2c_master_bus_add_device(i2c_master_bus_handle, &i2c_device_config, &i2c_master_dev_handle);

    uint8_t data[2] = {0x96, brightness};
    i2c_master_transmit(i2c_master_dev_handle, data, sizeof(data), 50);

    i2c_master_bus_rm_device(i2c_master_dev_handle);
}

static void display_panel_init(void)
{
    esp_ldo_channel_config_t esp_ldo_channel_config = {
        .chan_id = 3,
        .voltage_mv = 2500,
    };
    esp_ldo_channel_handle_t esp_ldo_channel_handle;
    esp_ldo_acquire_channel(&esp_ldo_channel_config, &esp_ldo_channel_handle);

    esp_lcd_dsi_bus_config_t esp_lcd_dsi_bus_config = JD9365_PANEL_BUS_DSI_2CH_CONFIG();
    esp_lcd_dsi_bus_handle_t esp_lcd_dsi_bus_handle;
    esp_lcd_new_dsi_bus(&esp_lcd_dsi_bus_config, &esp_lcd_dsi_bus_handle);

    esp_lcd_dbi_io_config_t esp_lcd_dbi_io_config = JD9365_PANEL_IO_DBI_CONFIG();
    esp_lcd_new_panel_io_dbi(esp_lcd_dsi_bus_handle, &esp_lcd_dbi_io_config, &esp_lcd_panel_io_handle);

    esp_lcd_dpi_panel_config_t esp_lcd_dpi_panel_config = JD9365_800_1280_PANEL_60HZ_DPI_CONFIG(LCD_COLOR_PIXEL_FORMAT_RGB565);
    esp_lcd_dpi_panel_config.num_fbs = esp_lv_adapter_get_required_frame_buffer_count(ESP_LV_ADAPTER_TEAR_AVOID_MODE_DEFAULT_MIPI_DSI, ESP_LV_ADAPTER_ROTATE_0);

    jd9365_vendor_config_t jd9365_vendor_config = {
        .mipi_config = {
            .dsi_bus = esp_lcd_dsi_bus_handle,
            .dpi_config = &esp_lcd_dpi_panel_config,
            .lane_num = 2,
        },
    };

    esp_lcd_panel_dev_config_t esp_lcd_panel_dev_config = {
        .bits_per_pixel = 16,
        .rgb_ele_order = LCD_RGB_ELEMENT_ORDER_RGB,
        .reset_gpio_num = GPIO_NUM_NC,
        .vendor_config = &jd9365_vendor_config,
    };
    esp_lcd_new_panel_jd9365(esp_lcd_panel_io_handle, &esp_lcd_panel_dev_config, &esp_lcd_panel_handle);
    esp_lcd_panel_reset(esp_lcd_panel_handle);
    esp_lcd_panel_init(esp_lcd_panel_handle);
}

static void display_touch_init(void)
{
    esp_lcd_panel_io_i2c_config_t esp_lcd_panel_io_i2c_config = ESP_LCD_TOUCH_IO_I2C_GT911_CONFIG();
    esp_lcd_panel_io_i2c_config.scl_speed_hz = 400000;

    esp_lcd_panel_io_handle_t esp_lcd_panel_io_handle;
    esp_lcd_new_panel_io_i2c(i2c_master_bus_handle, &esp_lcd_panel_io_i2c_config, &esp_lcd_panel_io_handle);

    esp_lcd_touch_config_t esp_lcd_touch_config = {
        .x_max = 800,
        .y_max = 1280,
        .rst_gpio_num = GPIO_NUM_NC,
        .int_gpio_num = GPIO_NUM_NC,
        .flags = {
            .mirror_x = false,
            .swap_xy = false,
        },
    };
    esp_lcd_touch_new_i2c_gt911(esp_lcd_panel_io_handle, &esp_lcd_touch_config, &esp_lcd_touch_handle);
}
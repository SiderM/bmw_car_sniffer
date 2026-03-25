#include "ui.h"

objects_t objects;

void ui_init(void)
{
    lv_display_t *display = lv_display_get_default();
    lv_theme_t *theme = lv_theme_default_init(display, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), true, &ui_font_ubuntu_22);
    lv_display_set_theme(display, theme);

    ui_subjects_init();
    ui_screens_init();

    ui_screen_load(SCREEN_ID_HOME);
}
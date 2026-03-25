#ifndef UI_SCREENS_H
#define UI_SCREENS_H

#include "lvgl.h"

typedef struct
{
    lv_obj_t *home;
} screens_t;

enum screens_enum
{
    SCREEN_ID_HOME = 1,
};

extern screens_t screens;

void ui_screens_init(void);
void ui_screen_load(enum screens_enum screen_id);
void ui_action_to_screen(lv_event_t *event);

void ui_screen_home_create(void);

#endif // UI_SCREENS_H
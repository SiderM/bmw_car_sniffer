#include "screens.h"

screens_t screens;

static int current_screen = -1;

static lv_obj_t *get_screen_by_id(int id)
{
    if (id == -1)
    {
        return 0;
    }

    return ((lv_obj_t **)&screens)[id];
}

void ui_screens_init(void)
{
    ui_screen_home_create();
}

void ui_screen_load(enum screens_enum screen_id)
{
    current_screen = screen_id - 1;
    lv_obj_t *screen = get_screen_by_id(current_screen);
    lv_screen_load_anim(screen, LV_SCREEN_LOAD_ANIM_FADE_IN, 200, 0, false);
}

void ui_action_to_screen(lv_event_t *event)
{
    enum screens_enum screen_id = (enum screens_enum)lv_event_get_user_data(event);
    ui_screen_load(screen_id);
}
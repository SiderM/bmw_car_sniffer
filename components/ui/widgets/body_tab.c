#include "widgets.h"
#include "fonts.h"
#include "subjects.h"

void ui_widget_body_tab_create(lv_obj_t *parent)
{
    {
        lv_obj_t *obj = lv_obj_create(parent);
        lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_STRETCH, 0, 1, LV_GRID_ALIGN_STRETCH, 0, 1);
        {
            lv_obj_t *parent = obj;
            {
                lv_obj_t *obj = lv_label_create(parent);
                lv_label_set_text(obj, "Передняя левая\n дверь");
                lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_align(obj, LV_ALIGN_TOP_MID, 0, 0);
            }
            {
                lv_obj_t *obj = lv_label_create(parent);
                lv_label_set_text(obj, "Закрыта");
                lv_obj_set_style_text_font(obj, &ui_font_ubuntu_36, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_center(obj);
            }
        }
    }
    {
        lv_obj_t *obj = lv_obj_create(parent);
        lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_STRETCH, 1, 1, LV_GRID_ALIGN_STRETCH, 0, 1);
        {
            lv_obj_t *parent = obj;
            {
                lv_obj_t *obj = lv_label_create(parent);
                lv_label_set_text(obj, "Передняя правая\n дверь");
                lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_align(obj, LV_ALIGN_TOP_MID, 0, 0);
            }
            {
                lv_obj_t *obj = lv_label_create(parent);
                lv_label_set_text(obj, "Закрыта");
                lv_obj_set_style_text_font(obj, &ui_font_ubuntu_36, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_center(obj);
            }
        }
    }
    {
        lv_obj_t *obj = lv_obj_create(parent);
        lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_STRETCH, 2, 1, LV_GRID_ALIGN_STRETCH, 0, 1);
        {
            lv_obj_t *parent = obj;
            {
                lv_obj_t *obj = lv_label_create(parent);
                lv_label_set_text(obj, "Капот");
                lv_obj_align(obj, LV_ALIGN_TOP_MID, 0, 0);
            }
            {
                lv_obj_t *obj = lv_label_create(parent);
                lv_label_set_text(obj, "Закрыт");
                lv_obj_set_style_text_font(obj, &ui_font_ubuntu_36, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_center(obj);
            }
        }
    }
    {
        lv_obj_t *obj = lv_obj_create(parent);
        lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_STRETCH, 0, 1, LV_GRID_ALIGN_STRETCH, 1, 1);
        {
            lv_obj_t *parent = obj;
            {
                lv_obj_t *obj = lv_label_create(parent);
                lv_label_set_text(obj, "Задняя левая\n дверь");
                lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_align(obj, LV_ALIGN_TOP_MID, 0, 0);
            }
            {
                lv_obj_t *obj = lv_label_create(parent);
                lv_label_set_text(obj, "Закрыта");
                lv_obj_set_style_text_font(obj, &ui_font_ubuntu_36, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_center(obj);
            }
        }
    }
    {
        lv_obj_t *obj = lv_obj_create(parent);
        lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_STRETCH, 1, 1, LV_GRID_ALIGN_STRETCH, 1, 1);
        {
            lv_obj_t *parent = obj;
            {
                lv_obj_t *obj = lv_label_create(parent);
                lv_label_set_text(obj, "Задняя правая\n дверь");
                lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_align(obj, LV_ALIGN_TOP_MID, 0, 0);
            }
            {
                lv_obj_t *obj = lv_label_create(parent);
                lv_label_set_text(obj, "Закрыта");
                lv_obj_set_style_text_font(obj, &ui_font_ubuntu_36, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_center(obj);
            }
        }
    }
    {
        lv_obj_t *obj = lv_obj_create(parent);
        lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_STRETCH, 2, 1, LV_GRID_ALIGN_STRETCH, 1, 1);
        {
            lv_obj_t *parent = obj;
            {
                lv_obj_t *obj = lv_label_create(parent);
                lv_label_set_text(obj, "Багажник");
                lv_obj_align(obj, LV_ALIGN_TOP_MID, 0, 0);
            }
            {
                lv_obj_t *obj = lv_label_create(parent);
                lv_label_set_text(obj, "Закрыт");
                lv_obj_set_style_text_font(obj, &ui_font_ubuntu_36, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_center(obj);
            }
        }
    }
    {
        lv_obj_t *obj = lv_obj_create(parent);
        lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_STRETCH, 0, 1, LV_GRID_ALIGN_STRETCH, 2, 1);
        lv_obj_set_flag(obj, LV_OBJ_FLAG_SCROLLABLE, LV_PART_MAIN | LV_STATE_DEFAULT);
        {
            lv_obj_t *parent = obj;
            {
                lv_obj_t *obj = lv_label_create(parent);
                lv_label_set_text(obj, "Габаритные огни");
                lv_obj_align(obj, LV_ALIGN_TOP_MID, 0, 0);
            }
            {
                lv_obj_t *obj = lv_label_create(parent);
                lv_label_set_text(obj, "Выключены");
                lv_obj_set_style_text_font(obj, &ui_font_ubuntu_36, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_center(obj);
            }
        }
    }
    {
        lv_obj_t *obj = lv_obj_create(parent);
        lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_STRETCH, 1, 1, LV_GRID_ALIGN_STRETCH, 2, 1);
        {
            lv_obj_t *parent = obj;
            {
                lv_obj_t *obj = lv_label_create(parent);
                lv_label_set_text(obj, "Ближний свет");
                lv_obj_align(obj, LV_ALIGN_TOP_MID, 0, 0);
            }
            {
                lv_obj_t *obj = lv_label_create(parent);
                lv_label_set_text(obj, "Выключен");
                lv_obj_set_style_text_font(obj, &ui_font_ubuntu_36, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_center(obj);
            }
        }
    }
    {
        lv_obj_t *obj = lv_obj_create(parent);
        lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_STRETCH, 2, 1, LV_GRID_ALIGN_STRETCH, 2, 1);
        {
            lv_obj_t *parent = obj;
            {
                lv_obj_t *obj = lv_label_create(parent);
                lv_label_set_text(obj, "Дальний свет");
                lv_obj_align(obj, LV_ALIGN_TOP_MID, 0, 0);
            }
            {
                lv_obj_t *obj = lv_label_create(parent);
                lv_label_set_text(obj, "Выключен");
                lv_obj_set_style_text_font(obj, &ui_font_ubuntu_36, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_center(obj);
            }
        }
    }
    {
        lv_obj_t *obj = lv_obj_create(parent);
        lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_STRETCH, 0, 1, LV_GRID_ALIGN_STRETCH, 3, 1);
        {
            lv_obj_t *parent = obj;
            {
                lv_obj_t *obj = lv_label_create(parent);
                lv_label_set_text(obj, "Температура\n на улице");
                lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_align(obj, LV_ALIGN_TOP_MID, 0, 0);
            }
            {
                lv_obj_t *obj = lv_label_create(parent);
                lv_label_set_text(obj, "0");
                lv_obj_set_style_text_font(obj, &ui_font_ubuntu_42, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_center(obj);
            }
        }
    }
}
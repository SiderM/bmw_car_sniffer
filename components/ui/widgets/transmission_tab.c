#include "widgets.h"
#include "fonts.h"
#include "subjects.h"

void ui_widget_transmission_tab_create(lv_obj_t *parent)
{
    {
        lv_obj_t *obj = lv_obj_create(parent);
        lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_STRETCH, 0, 1, LV_GRID_ALIGN_STRETCH, 0, 1);
        {
            lv_obj_t *parent = obj;
            {
                lv_obj_t *obj = lv_label_create(parent);
                lv_label_set_text(obj, "Ошибка ABS");
                lv_obj_align(obj, LV_ALIGN_TOP_MID, 0, 0);
            }
            {
                lv_obj_t *obj = lv_label_create(parent);
                lv_label_bind_text(obj, &subjects.abs, "%s");
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
                lv_label_set_text(obj, "Ошибка DSC");
                lv_obj_align(obj, LV_ALIGN_TOP_MID, 0, 0);
            }
            {
                lv_obj_t *obj = lv_label_create(parent);
                lv_label_bind_text(obj, &subjects.dsc, "%s");
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
                lv_label_set_text(obj, "Уровень ТЖ");
                lv_obj_align(obj, LV_ALIGN_TOP_MID, 0, 0);
            }
            {
                lv_obj_t *obj = lv_label_create(parent);
                lv_label_bind_text(obj, &subjects.break_fluid, "%s");
                lv_obj_set_style_text_font(obj, &ui_font_ubuntu_36, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_center(obj);
            }
        }
    }
    {
        lv_obj_t *obj = lv_obj_create(parent);
        lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_STRETCH, 0, 1, LV_GRID_ALIGN_STRETCH, 1, 1);
        lv_obj_set_flag(obj, LV_OBJ_FLAG_SCROLLABLE, LV_PART_MAIN | LV_STATE_DEFAULT);
        {
            lv_obj_t *parent = obj;
            {
                lv_obj_t *obj = lv_label_create(parent);
                lv_label_set_text(obj, "Тормозные колодки");
                lv_obj_align(obj, LV_ALIGN_TOP_MID, 0, 0);
            }
            {
                lv_obj_t *obj = lv_label_create(parent);
                lv_label_bind_text(obj, &subjects.break_pads, "%s");
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
                lv_label_set_text(obj, "Скорость");
                lv_obj_align(obj, LV_ALIGN_TOP_MID, 0, 0);
            }
            {
                lv_obj_t *obj = lv_label_create(parent);
                lv_label_bind_text(obj, &subjects.speed, "%d");
                lv_obj_set_style_text_font(obj, &ui_font_ubuntu_42, LV_PART_MAIN | LV_STATE_DEFAULT);
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
                lv_label_set_text(obj, "Передача");
                lv_obj_align(obj, LV_ALIGN_TOP_MID, 0, 0);
            }
            {
                lv_obj_t *obj = lv_label_create(parent);
                lv_label_bind_text(obj, &subjects.gear, "%s");
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
                lv_label_set_text(obj, "Ручной тормоз");
                lv_obj_align(obj, LV_ALIGN_TOP_MID, 0, 0);
            }
            {
                lv_obj_t *obj = lv_label_create(parent);
                lv_label_bind_text(obj, &subjects.handbreak, "%s");
                lv_obj_set_style_text_font(obj, &ui_font_ubuntu_36, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_center(obj);
            }
        }
    }
    {
        lv_obj_t *obj = lv_obj_create(parent);
        lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_STRETCH, 1, 1, LV_GRID_ALIGN_STRETCH, 2, 1);
        lv_obj_set_flag(obj, LV_OBJ_FLAG_SCROLLABLE, LV_PART_MAIN | LV_STATE_DEFAULT);
        {
            lv_obj_t *parent = obj;
            {
                lv_obj_t *obj = lv_label_create(parent);
                lv_label_set_text(obj, "Ошибка АКПП");
                lv_obj_align(obj, LV_ALIGN_TOP_MID, 0, 0);
            }
            {
                lv_obj_t *obj = lv_label_create(parent);
                lv_label_bind_text(obj, &subjects.transmission, "%s");
                lv_obj_set_style_text_font(obj, &ui_font_ubuntu_36, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_center(obj);
            }
        }
    }
    {
        lv_obj_t *obj = lv_obj_create(parent);
        lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_STRETCH, 2, 1, LV_GRID_ALIGN_STRETCH, 2, 1);
        lv_obj_set_flag(obj, LV_OBJ_FLAG_SCROLLABLE, LV_PART_MAIN | LV_STATE_DEFAULT);
        {
            lv_obj_t *parent = obj;
            {
                lv_obj_t *obj = lv_label_create(parent);
                lv_label_set_text(obj, "Пробег");
                lv_obj_align(obj, LV_ALIGN_TOP_MID, 0, 0);
            }
            {
                lv_obj_t *obj = lv_label_create(parent);
                lv_label_bind_text(obj, &subjects.mileage, "%d");
                lv_obj_set_style_text_font(obj, &ui_font_ubuntu_42, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_center(obj);
            }
        }
    }
}
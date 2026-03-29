#include "widgets.h"
#include "fonts.h"
#include "subjects.h"

static lv_obj_t *rpm_chart;

static void ui_update_timer(lv_timer_t *timer)
{
    lv_chart_set_next_value(rpm_chart, lv_chart_get_series_next(rpm_chart, NULL), lv_subject_get_int(&subjects.rpm));
}

void ui_widget_engine_tab_create(lv_obj_t *parent)
{
    lv_timer_create(ui_update_timer, 100, NULL);

    {
        lv_obj_t *obj = lv_obj_create(parent);
        lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_STRETCH, 0, 1, LV_GRID_ALIGN_STRETCH, 0, 1);
        lv_obj_remove_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
        {
            lv_obj_t *parent = obj;
            {
                lv_obj_t *obj = lv_label_create(parent);
                lv_label_set_text(obj, "Зажигание");
                lv_obj_align(obj, LV_ALIGN_TOP_MID, 0, 0);
            }
            {
                lv_obj_t *obj = lv_label_create(parent);
                lv_label_bind_text(obj, &subjects.ignition, "%s");
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
                lv_label_set_text(obj, "Состояние ДВС");
                lv_obj_align(obj, LV_ALIGN_TOP_MID, 0, 0);
            }
            {
                lv_obj_t *obj = lv_label_create(parent);
                lv_label_bind_text(obj, &subjects.engine, "%s");
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
                lv_label_set_text(obj, "Check Engine");
                lv_obj_align(obj, LV_ALIGN_TOP_MID, 0, 0);
            }
            {
                lv_obj_t *obj = lv_label_create(parent);
                lv_label_bind_text(obj, &subjects.check, "%s");
                lv_obj_set_style_text_font(obj, &ui_font_ubuntu_36, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_center(obj);
            }
        }
    }
    {
        lv_obj_t *obj = lv_obj_create(parent);
        lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_STRETCH, 0, 2, LV_GRID_ALIGN_STRETCH, 1, 1);
        {
            lv_obj_t *parent = obj;
            {
                lv_obj_t *obj = lv_label_create(parent);
                lv_label_set_text(obj, "Обороты двигателя");
                lv_obj_align(obj, LV_ALIGN_TOP_MID, 0, 0);
            }
            {
                lv_obj_t *obj = lv_chart_create(parent);
                rpm_chart = obj;
                lv_obj_set_height(obj, 120);
                lv_chart_set_update_mode(obj, LV_CHART_UPDATE_MODE_SHIFT);
                lv_obj_set_style_size(obj, 0, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
                lv_chart_add_series(obj, lv_palette_main(LV_PALETTE_RED), LV_CHART_AXIS_PRIMARY_Y);
                lv_chart_set_axis_range(obj, LV_CHART_AXIS_PRIMARY_Y, 0, 7000);
                lv_chart_set_point_count(obj, 50);
                lv_obj_align(obj, LV_ALIGN_BOTTOM_MID, 0, 0);
                {
                    lv_obj_t *parent = obj;
                    {
                        lv_obj_t *obj = lv_label_create(parent);
                        lv_label_bind_text(obj, &subjects.rpm, "%d");
                        lv_obj_set_style_text_font(obj, &ui_font_ubuntu_42, LV_PART_MAIN | LV_STATE_DEFAULT);
                        lv_obj_center(obj);
                    }
                }
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
                lv_label_set_text(obj, "Давление масла");
                lv_obj_align(obj, LV_ALIGN_TOP_MID, 0, 0);
            }
            {
                lv_obj_t *obj = lv_label_create(parent);
                lv_label_bind_text(obj, &subjects.oil_pressure, "%s");
                lv_obj_set_style_text_font(obj, &ui_font_ubuntu_36, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_center(obj);
            }
        }
    }
    {
        lv_obj_t *obj = lv_obj_create(parent);
        lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_STRETCH, 0, 1, LV_GRID_ALIGN_STRETCH, 2, 1);
        {
            lv_obj_t *parent = obj;
            {
                lv_obj_t *obj = lv_label_create(parent);
                lv_label_set_text(obj, "Температура ОЖ");
                lv_obj_align(obj, LV_ALIGN_TOP_MID, 0, 0);
            }
            {
                lv_obj_t *obj = lv_label_create(parent);
                lv_label_bind_text(obj, &subjects.coolant_temp, "%d");
                lv_obj_set_style_text_font(obj, &ui_font_ubuntu_42, LV_PART_MAIN | LV_STATE_DEFAULT);
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
                lv_label_set_text(obj, "Ошибка EML");
                lv_obj_align(obj, LV_ALIGN_TOP_MID, 0, 0);
            }
            {
                lv_obj_t *obj = lv_label_create(parent);
                lv_label_bind_text(obj, &subjects.eml, "%s");
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
                lv_label_set_text(obj, "Зарядка");
                lv_obj_align(obj, LV_ALIGN_TOP_MID, 0, 0);
            }
            {
                lv_obj_t *obj = lv_label_create(parent);
                lv_label_bind_text(obj, &subjects.charge, "%s");
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
                lv_label_set_text(obj, "Уровень ОЖ");
                lv_obj_align(obj, LV_ALIGN_TOP_MID, 0, 0);
            }
            {
                lv_obj_t *obj = lv_label_create(parent);
                lv_label_bind_text(obj, &subjects.coolant_level, "%s");
                lv_obj_set_style_text_font(obj, &ui_font_ubuntu_36, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_center(obj);
            }
        }
    }
    {
        lv_obj_t *obj = lv_obj_create(parent);
        lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_STRETCH, 1, 1, LV_GRID_ALIGN_STRETCH, 3, 1);
        {
            lv_obj_t *parent = obj;
            {
                lv_obj_t *obj = lv_label_create(parent);
                lv_label_set_text(obj, "Уровень масла");
                lv_obj_align(obj, LV_ALIGN_TOP_MID, 0, 0);
            }
            {
                lv_obj_t *obj = lv_label_create(parent);
                lv_label_bind_text(obj, &subjects.oil_level, "%s");
                lv_obj_set_style_text_font(obj, &ui_font_ubuntu_36, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_center(obj);
            }
        }
    }
    {
        lv_obj_t *obj = lv_obj_create(parent);
        lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_STRETCH, 2, 1, LV_GRID_ALIGN_STRETCH, 3, 1);
        {
            lv_obj_t *parent = obj;
            {
                lv_obj_t *obj = lv_label_create(parent);
                lv_label_set_text(obj, "Уровень топлива");
                lv_obj_align(obj, LV_ALIGN_TOP_MID, 0, 0);
            }
            {
                lv_obj_t *obj = lv_label_create(parent);
                lv_label_bind_text(obj, &subjects.fuel_liters, "%d");
                lv_obj_set_style_text_font(obj, &ui_font_ubuntu_42, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_center(obj);
            }
        }
    }
}
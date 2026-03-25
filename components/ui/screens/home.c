#include "screens.h"
#include "fonts.h"
#include "subjects.h"
#include "widgets.h"

void ui_screen_home_create(void)
{
    static int32_t col_dsc[] = {LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};
    static int32_t row_dsc[] = {LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};

    lv_obj_t *obj = lv_obj_create(NULL);
    screens.home = obj;
    {
        lv_obj_t *parent = obj;
        {
            lv_obj_t *obj = lv_tabview_create(parent);
            lv_obj_set_style_text_font(lv_tabview_get_tab_bar(obj), &ui_font_ubuntu_24, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent = obj;
                {
                    lv_obj_t *obj = lv_tabview_add_tab(parent, "Двигатель");
                    lv_obj_set_layout(obj, LV_LAYOUT_GRID);
                    lv_obj_set_style_grid_column_dsc_array(obj, col_dsc, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_grid_row_dsc_array(obj, row_dsc, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent = obj;
                        {
                            ui_widget_engine_tab_create(parent);
                        }
                    }
                }
                {
                    lv_obj_t *obj = lv_tabview_add_tab(parent, "Трансмиссия");
                    lv_obj_set_layout(obj, LV_LAYOUT_GRID);
                    lv_obj_set_style_grid_column_dsc_array(obj, col_dsc, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_grid_row_dsc_array(obj, row_dsc, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent = obj;
                        {
                            ui_widget_transmission_tab_create(parent);
                        }
                    }
                }
                {
                    lv_obj_t *obj = lv_tabview_add_tab(parent, "Кузов");
                    lv_obj_set_layout(obj, LV_LAYOUT_GRID);
                    lv_obj_set_style_grid_column_dsc_array(obj, col_dsc, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_grid_row_dsc_array(obj, row_dsc, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent = obj;
                        {
                            ui_widget_body_tab_create(parent);
                        }
                    }
                }
            }
        }
    }
}
#include "subjects.h"

subjects_t subjects;

static char ignition[32];
static char engine[32];
static char check[32];
static char oil_pressure[32];
static char eml[32];
static char battery[32];
static char coolant_level[32];
static char oil_level[32];

void ui_subjects_init(void)
{
    lv_subject_init_string(&subjects.ignition, ignition, NULL, sizeof(ignition), "Выключено");
    lv_subject_init_string(&subjects.engine, engine, NULL, sizeof(engine), "Выключен");
    lv_subject_init_string(&subjects.check, check, NULL, sizeof(check), "Нет");
    lv_subject_init_int(&subjects.rpm, 0);
    lv_subject_init_string(&subjects.oil_pressure, oil_pressure, NULL, sizeof(oil_pressure), "Нет");
    lv_subject_init_int(&subjects.coolant_temp, 0);
    lv_subject_init_string(&subjects.eml, eml, NULL, sizeof(eml), "Нет");
    lv_subject_init_string(&subjects.battery, battery, NULL, sizeof(battery), "Нет");
    lv_subject_init_string(&subjects.coolant_level, coolant_level, NULL, sizeof(coolant_level), "Норма");
    lv_subject_init_string(&subjects.oil_level, oil_level, NULL, sizeof(oil_level), "Норма");
    lv_subject_init_int(&subjects.fuel_liters, 0);
}
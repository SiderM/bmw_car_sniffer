#ifndef UI_SUBJECTS_H
#define UI_SUBJECTS_H

#include "lvgl.h"

typedef struct
{
    lv_subject_t ignition;
    lv_subject_t engine;
    lv_subject_t check;
    lv_subject_t rpm;
    lv_subject_t oil_pressure;
    lv_subject_t coolant_temp;
    lv_subject_t eml;
    lv_subject_t battery;
    lv_subject_t coolant_level;
    lv_subject_t oil_level;
    lv_subject_t fuel_liters;
} subjects_t;

extern subjects_t subjects;

void ui_subjects_init(void);

#endif // UI_SUBJECTS_H
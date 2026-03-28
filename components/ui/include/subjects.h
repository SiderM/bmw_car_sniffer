#ifndef UI_SUBJECTS_H
#define UI_SUBJECTS_H

#include "lvgl.h"

typedef struct
{
    // Двигатель
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
    // Трансмиссия
    lv_subject_t abs;
    lv_subject_t dsc;
    lv_subject_t break_fluid;
    lv_subject_t break_pads;
    lv_subject_t speed;
    lv_subject_t gear;
    lv_subject_t handbreak;
    lv_subject_t gearbox;
    lv_subject_t odometer;
    // Кузов
    lv_subject_t door_driver;
    lv_subject_t door_passenger;
    lv_subject_t front_lid;
    lv_subject_t door_rear_left;
    lv_subject_t door_rear_right;
    lv_subject_t rear_lid;
    lv_subject_t parking;
    lv_subject_t beam_low;
    lv_subject_t beam_high;
    lv_subject_t fog_front;
    lv_subject_t fog_rear;
    lv_subject_t ambient;
} subjects_t;

extern subjects_t subjects;

void ui_subjects_init(void);

#endif // UI_SUBJECTS_H
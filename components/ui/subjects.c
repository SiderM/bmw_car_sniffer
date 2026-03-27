#include "subjects.h"

subjects_t subjects;

// Двигатель
static char ignition[32];
static char engine[32];
static char check[32];
static char oil_pressure[32];
static char eml[32];
static char battery[32];
static char coolant_level[32];
static char oil_level[32];

// Трансмиссия
static char abs_err[32];
static char dsc[32];
static char break_fluid[32];
static char break_pads[32];
static char gear[32];
static char handbreak[32];
static char gearbox[32];

// Кузов
static char door_front_left[32];
static char door_front_right[32];
static char front_lid[32];
static char door_rear_left[32];
static char door_rear_right[32];
static char rear_lid[32];
static char parking[32];
static char beam_low[32];
static char beam_high[32];
static char fog_front[32];
static char fog_rear[32];

void ui_subjects_init(void)
{
    // Двигатель
    lv_subject_init_string(&subjects.ignition, ignition, NULL, sizeof(ignition), "---");
    lv_subject_init_string(&subjects.engine, engine, NULL, sizeof(engine), "---");
    lv_subject_init_string(&subjects.check, check, NULL, sizeof(check), "---");
    lv_subject_init_int(&subjects.rpm, 0);
    lv_subject_init_string(&subjects.oil_pressure, oil_pressure, NULL, sizeof(oil_pressure), "---");
    lv_subject_init_int(&subjects.coolant_temp, 0);
    lv_subject_init_string(&subjects.eml, eml, NULL, sizeof(eml), "---");
    lv_subject_init_string(&subjects.battery, battery, NULL, sizeof(battery), "---");
    lv_subject_init_string(&subjects.coolant_level, coolant_level, NULL, sizeof(coolant_level), "---");
    lv_subject_init_string(&subjects.oil_level, oil_level, NULL, sizeof(oil_level), "---");
    lv_subject_init_int(&subjects.fuel_liters, 0);

    // Трансмиссия
    lv_subject_init_string(&subjects.abs, abs_err, NULL, sizeof(abs_err), "---");
    lv_subject_init_string(&subjects.dsc, dsc, NULL, sizeof(dsc), "---");
    lv_subject_init_string(&subjects.break_fluid, break_fluid, NULL, sizeof(break_fluid), "---");
    lv_subject_init_string(&subjects.break_pads, break_pads, NULL, sizeof(break_pads), "---");
    lv_subject_init_int(&subjects.speed, 0);
    lv_subject_init_string(&subjects.gear, gear, NULL, sizeof(gear), "---");
    lv_subject_init_string(&subjects.handbreak, handbreak, NULL, sizeof(handbreak), "---");
    lv_subject_init_string(&subjects.gearbox, gearbox, NULL, sizeof(gearbox), "---");
    lv_subject_init_int(&subjects.odometer, 0);

    // Кузов
    lv_subject_init_string(&subjects.door_front_left, door_front_left, NULL, sizeof(door_front_left), "---");
    lv_subject_init_string(&subjects.door_front_right, door_front_right, NULL, sizeof(door_front_right), "---");
    lv_subject_init_string(&subjects.front_lid, front_lid, NULL, sizeof(front_lid), "---");
    lv_subject_init_string(&subjects.door_rear_left, door_rear_left, NULL, sizeof(door_rear_left), "---");
    lv_subject_init_string(&subjects.door_rear_right, door_rear_right, NULL, sizeof(door_rear_right), "---");
    lv_subject_init_string(&subjects.rear_lid, rear_lid, NULL, sizeof(rear_lid), "---");
    lv_subject_init_string(&subjects.parking, parking, NULL, sizeof(parking), "---");
    lv_subject_init_string(&subjects.beam_low, beam_low, NULL, sizeof(beam_low), "---");
    lv_subject_init_string(&subjects.beam_high, beam_high, NULL, sizeof(beam_high), "---");
    lv_subject_init_string(&subjects.fog_front, fog_front, NULL, sizeof(fog_front), "---");
    lv_subject_init_string(&subjects.fog_rear, fog_rear, NULL, sizeof(fog_rear), "---");
    lv_subject_init_int(&subjects.outside_temp, 0);
}
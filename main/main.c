#include <math.h>
#include "display.h"
#include "kbus.h"
#include "can.h"
#include "ui.h"

static void kbus_on_recv(const kbus_frame_t *frame)
{
    // ESP_LOGI("KBUS_RX", "SRC: 0x%02X LEN: 0x%02X DST: 0x%02X CMD: 0x%02X CRC: 0x%02X", frame->src, frame->len, frame->dst, frame->cmd, frame->crc);
    // ESP_LOG_BUFFER_HEX("KBUS_RX", frame->data, frame->data_len);

    switch (frame->cmd)
    {
    case KBUS_CMD_IGNITION:
        esp_lv_adapter_lock(-1);
        if (frame->data[0] & IGNITION_KL_30)
        {
            lv_subject_copy_string(&subjects.ignition, "KL_30");
        }
        else if (frame->data[0] & IGNITION_KL_R)
        {
            lv_subject_copy_string(&subjects.ignition, "KL_R");
        }
        else if (frame->data[0] & IGNITION_KL_15)
        {
            lv_subject_copy_string(&subjects.ignition, "KL_15");
        }
        else if (frame->data[0] & IGNITION_KL_50)
        {
            lv_subject_copy_string(&subjects.ignition, "KL_50");
        }
        esp_lv_adapter_unlock();
        break;
    case KBUS_CMD_SENSORS:
        esp_lv_adapter_lock(-1);
        lv_subject_copy_string(&subjects.handbreak, (frame->data[0] & HANDBRAKE) ? "Вкл." : "Выкл.");
        lv_subject_copy_string(&subjects.oil_pressure, (frame->data[0] & OIL_PRESSURE) ? "Нет" : "Есть");
        lv_subject_copy_string(&subjects.break_pads, (frame->data[0] & BRAKE_PADS) ? "Износ" : "Норма");
        lv_subject_copy_string(&subjects.transmission, (frame->data[0] & TRANSMISSION) ? "Ошибка" : "Норма");
        lv_subject_copy_string(&subjects.engine, (frame->data[1] & ENGINE) ? "Работает" : "Выкл.");

        uint8_t gear = frame->data[1];

        if ((gear == GEAR_PARK) || (gear == GEAR_PARK + ENGINE) || (gear == GEAR_PARK + ENGINE + DOOR))
        {
            lv_subject_copy_string(&subjects.gear, "P");
        }
        else if ((gear == GEAR_REVERSE) || (gear == GEAR_REVERSE + ENGINE) || (gear == GEAR_PARK + ENGINE + DOOR))
        {
            lv_subject_copy_string(&subjects.gear, "R");
        }
        else if ((gear == GEAR_NEUTRAL) || (gear == GEAR_NEUTRAL + ENGINE) || (gear == GEAR_PARK + ENGINE + DOOR))
        {
            lv_subject_copy_string(&subjects.gear, "N");
        }
        else if ((gear == GEAR_DRIVE) || (gear == GEAR_DRIVE + ENGINE) || (gear == GEAR_PARK + ENGINE + DOOR))
        {
            lv_subject_copy_string(&subjects.gear, "D");
        }
        else if ((gear == GEAR_FIRST) || (gear == GEAR_FIRST + ENGINE) || (gear == GEAR_PARK + ENGINE + DOOR))
        {
            lv_subject_copy_string(&subjects.gear, "M1");
        }
        else if ((gear == GEAR_SECOND) || (gear == GEAR_SECOND + ENGINE) || (gear == GEAR_PARK + ENGINE + DOOR))
        {
            lv_subject_copy_string(&subjects.gear, "M2");
        }
        else if ((gear == GEAR_THIRD) || (gear == GEAR_THIRD + ENGINE) || (gear == GEAR_PARK + ENGINE + DOOR))
        {
            lv_subject_copy_string(&subjects.gear, "M3");
        }
        else if ((gear == GEAR_FOURTH) || (gear == GEAR_FOURTH + ENGINE) || (gear == GEAR_PARK + ENGINE + DOOR))
        {
            lv_subject_copy_string(&subjects.gear, "M4");
        }
        else if ((gear == GEAR_FIFTH) || (gear == GEAR_FIFTH + ENGINE) || (gear == GEAR_PARK + ENGINE + DOOR))
        {
            lv_subject_copy_string(&subjects.gear, "M5");
        }
        esp_lv_adapter_unlock();
        break;
    case KBUS_CMD_ODOMETER:
        esp_lv_adapter_lock(-1);
        lv_subject_set_int(&subjects.mileage, (frame->data[2] * 65536) + (frame->data[1] * 256) + frame->data[0]);
        esp_lv_adapter_unlock();
        break;
    case KBUS_CMD_TEMPERATURE:
        esp_lv_adapter_lock(-1);
        lv_subject_set_int(&subjects.ambient, frame->data[0]);
        lv_subject_set_int(&subjects.coolant_temp, frame->data[1]);
        esp_lv_adapter_unlock();
        break;
    case KBUS_CMD_CHECK_CONTROL_STATUS:
        esp_lv_adapter_lock(-1);
        lv_subject_copy_string(&subjects.break_fluid, (frame->data[0] & BRAKE_FLUID) ? "Норма" : "Низкий");
        lv_subject_copy_string(&subjects.oil_level, (frame->data[0] & OIL_LEVEL) ? "Норма" : "Низкий");
        esp_lv_adapter_unlock();
        break;
    case KBUS_CMD_CLUSTER_INDICATORS:
        esp_lv_adapter_lock(-1);
        lv_subject_copy_string(&subjects.fog_rear, (frame->data[0] & FOG_REAR) ? "Вкл." : "Выкл.");
        lv_subject_copy_string(&subjects.fog_front, (frame->data[0] & FOG_FRONT) ? "Вкл." : "Выкл.");
        lv_subject_copy_string(&subjects.beam_high, (frame->data[0] & BEAM_HIGH) ? "Вкл." : "Выкл.");
        lv_subject_copy_string(&subjects.beam_low, (frame->data[0] & BEAM_LOW) ? "Вкл." : "Выкл.");
        lv_subject_copy_string(&subjects.parking, (frame->data[0] & PARKING) ? "Вкл." : "Выкл.");
        lv_subject_copy_string(&subjects.turn_left, (frame->data[0] & TURN_LEFT) ? "Вкл." : "Выкл.");
        lv_subject_copy_string(&subjects.turn_right, (frame->data[0] & TURN_RIGHT) ? "Вкл." : "Выкл.");
        esp_lv_adapter_unlock();
        break;
    case KBUS_CMD_INSTRUMENT_BACKLIGHT:
        display_brightness_set(frame->data[0]);
        break;
    case KBUS_CMD_DOOR_LID_SATTUS:
        esp_lv_adapter_lock(-1);
        lv_subject_copy_string(&subjects.door_driver, (frame->data[0] & DOOR_DRIVER) ? "Открыта" : "Закрыта");
        lv_subject_copy_string(&subjects.door_passenger, (frame->data[0] & DOOR_PASSENGER) ? "Открыта" : "Закрыта");
        lv_subject_copy_string(&subjects.door_rear_lh, (frame->data[0] & DOOR_REAR_LH) ? "Открыта" : "Закрыта");
        lv_subject_copy_string(&subjects.door_rear_rh, (frame->data[0] & DOOR_REAR_RH) ? "Открыта" : "Закрыта");

        lv_subject_copy_string(&subjects.rear_lid, (frame->data[1] & REAR_LID) ? "Открыт" : "Закрыт");
        lv_subject_copy_string(&subjects.front_lid, (frame->data[1] & FRONT_LID) ? "Открыт" : "Закрыт");
        esp_lv_adapter_unlock();
        break;

    default:
        break;
    }
}

static void can_on_recv(const can_frame_t *frame)
{
    // ESP_LOGI("CAN_RX", "ID: 0x%03X", frame->id);
    // ESP_LOG_BUFFER_HEX("CAN_RX", frame->data, frame->data_len);

    switch (frame->id)
    {
    case CAN_ID_ASC1:
        uint16_t speed_combined = (uint16_t)frame->data[2] << 8 | frame->data[1];
        uint16_t speed_raw = (speed_combined >> 4) & 0x0FFF;
        float speed_kmh = speed_raw / 8.0f;
        esp_lv_adapter_lock(-1);
        lv_subject_set_int(&subjects.speed, (int)round(speed_kmh));
        esp_lv_adapter_unlock();
        break;
    case CAN_ID_SWS1:
        uint16_t word_a = (uint16_t)frame->data[0] | ((uint16_t)frame->data[1] << 8);
        uint16_t angle_raw = word_a & 0x7FFF;
        uint8_t angle_sign = (word_a >> 15) & 1;
        float angle_deg = (angle_sign ? -1.0f : 1.0f) * angle_raw * 0.045f;
        esp_lv_adapter_lock(-1);
        lv_subject_set_int(&subjects.angle, (int)angle_deg);
        esp_lv_adapter_unlock();
        break;
    case CAN_ID_DME1:
        uint16_t rpm_raw = ((uint16_t)frame->data[3] << 8) | frame->data[2];
        float rpm = rpm_raw / 6.4f;
        esp_lv_adapter_lock(-1);
        lv_subject_set_int(&subjects.rpm, (int)rpm);
        esp_lv_adapter_unlock();
        break;
    case CAN_ID_DME4:
        esp_lv_adapter_lock(-1);
        lv_subject_copy_string(&subjects.check, (frame->data[0] & 0x02) ? "Вкл." : "Выкл.");
        lv_subject_copy_string(&subjects.eml, (frame->data[0] & 0x10) ? "Вкл." : "Выкл.");
        lv_subject_copy_string(&subjects.charge, (frame->data[5] & 0x01) ? "Нет" : "Есть");
        esp_lv_adapter_unlock();
        break;
    case CAN_ID_IKE1:
        float fuel_percent = 0.0f;
        bool low_fuel = false;
        bool empty = false;

        if (frame->data[2] >= 0x80)
        {
            // Зона ниже лампы: 0x80 (пусто) → 0x87 (граница)
            float low_ceil = (float)(0x08 - 0) * 100.0f / (0x39 - 0);
            fuel_percent = ((float)(frame->data[2] - 0x80) / 7.0f) * low_ceil;
            low_fuel = true;
            empty = (frame->data[2] == 0x80);
        }
        else if (frame->data[2] >= 0x08)
        {
            // Основной диапазон: 0x08 (лампа) → 0x39 (полный)
            fuel_percent = (float)(frame->data[2] - 0x08) / (float)(0x39 - 0x08) * 100.0f;
            low_fuel = (frame->data[2] == 0x08);
        }
        else
        {
            fuel_percent = 0.0f;
            low_fuel = true;
            empty = true;
        }
        esp_lv_adapter_lock(-1);
        lv_subject_set_int(&subjects.fuel_liters, (int)(fuel_percent * 60.0f / 100.0f));
        esp_lv_adapter_unlock();
        break;

    default:
        break;
    }
}

void app_main(void)
{
    kbus_config_t kbus_config = {
        .uart_num = UART_NUM_1,
        .uart_rx_io = GPIO_NUM_21,
        .uart_tx_io = GPIO_NUM_22,
    };
    kbus_init(&kbus_config);
    kbus_register_recv_cb(kbus_on_recv);

    can_config_t can_config = {
        .twai_rx_io = GPIO_NUM_6,
        .twai_tx_io = GPIO_NUM_5,
        .bitrate = 500000,
    };
    can_init(&can_config);
    can_register_recv_cb(can_on_recv);

    display_init();
    esp_lv_adapter_lock(-1);
    ui_init();
    esp_lv_adapter_unlock();
}

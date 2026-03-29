#ifndef KBUS_DEFS_H
#define KBUS_DEFS_H

#define KBUS_CMD_IGNITION 0x11
#define KBUS_CMD_SENSORS 0x13
#define KBUS_CMD_ODOMETER 0x17
#define KBUS_CMD_TEMPERATURE 0x19
#define KBUS_CMD_CHECK_CONTROL_STATUS 0x51
#define KBUS_CMD_CLUSTER_INDICATORS 0x5B
#define KBUS_CMD_INSTRUMENT_BACKLIGHT 0x5C
#define KBUS_CMD_DOOR_LID_SATTUS 0x7A

/* ------------------ 0x11 Ignition ------------------ */
// Byte 1
#define IGNITION_KL_30 0x00
#define IGNITION_KL_R 0x01
#define IGNITION_KL_15 0x02
#define IGNITION_KL_50 0x07

/* ------------------ 0x13 Sensors ------------------ */
// Byte 1
#define HANDBRAKE 0x01
#define OIL_PRESSURE 0x02
#define BRAKE_PADS 0x04
#define TRANSMISSION 0x10
// Byte 2
#define ENGINE 0x01
#define GEAR_PARK 0xB0
#define GEAR_REVERSE 0x10
#define GEAR_NEUTRAL 0x70
#define GEAR_DRIVE 0x80
#define GEAR_FIRST 0x20
#define GEAR_SECOND 0x60
#define GEAR_THIRD 0xD0
#define GEAR_FOURTH 0xC0
#define GEAR_FIFTH 0xE0

/* ------------------0x51 Check Control Status ------------------ */
// Byte 1
#define BRAKE_FLUID 0x01
#define OIL_LEVEL 0x40

/* ------------------ 0x5b Cluster Indicators ------------------ */
// Byte 1
#define FOG_REAR 0x10
#define FOG_FRONT 0x08
#define BEAM_HIGH 0x04
#define BEAM_LOW 0x02
#define PARKING 0x01

/* ------------------ 0x7a Door/Lid Status ------------------ */
// Byte 1
#define DOOR_DRIVER 0x01
#define DOOR_PASSENGER 0x02
#define DOOR_REAR_RH 0x04
#define DOOR_REAR_LH 0x08
// Byte 2
#define REAR_LID 0x20
#define FRONT_LID 0x40

#endif // KBUS_CMDS_H
#ifndef KBUS_DEFS_H
#define KBUS_DEFS_H

#define KBUS_CMD_TEMPERATURE 0x19
#define KBUS_CMD_CLUSTER_INDICATORS 0x5B
#define KBUS_CMD_INSTRUMENT_BACKLIGHT 0x5C
#define KBUS_CMD_DOOR_LID_SATTUS 0x7A

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
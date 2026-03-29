#ifndef CAN_DEFS_H
#define CAN_DEFS_H

#define CAN_ID_ASC1 0x153
#define CAN_ID_DME1 0x316
#define CAN_ID_DME4 0x545
#define CAN_ID_IKE1 0x613

/* ------------------ 0x545 DME4 ------------------ */
// Byte 0
#define CHECK_ENGINE 0x02
#define CRUISE 0x08
#define EML 0x10
// Byte 5
#define CHARGE 0x01

#endif // CAN_DEFS_H
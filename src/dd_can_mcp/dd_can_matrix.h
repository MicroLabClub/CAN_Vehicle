#ifndef DD_CAN_MATRIX_H_
#define DD_CAN_MATRIX_H_
#include <stdint.h>

#define CAN_ID_BUZZER   0x111
#define CAN_ID_CRISTI_S 0x112
#define CAN_ID_CRISTI_P 0x113
#define CAN_ID_ADRIAN_B 0x121
#define CAN_ID_DORIN_A  0x128
#define CAN_ID_MIHAIL_P 0x129
#define CAN_ID_ROMAN_A  0x125
#define CAN_ID_MAINCTRL 0x126
#define CAN_ID_VICTOR_C 0x124
#define CAN_ID_DAVID_C  0x123
#define CAN_ID_JOYSTICK 0x222

#define TX_CAN_ID_NR_OF 1
#define TX_CAN_ID_LIST {CAN_ID_BUZZER}


enum Can_Matrix_ID
{
    CAN_MSG_0,
    CAN_MSG_1,
    CAN_MSG_2,
    CAN_MSG_3,
    CAN_MSG_4,
    CAN_MSG_5,
    CAN_MSG_6,
    CAN_MSG_7,
    CAN_MSG_8,
    CAN_MSG_9,
    CAN_MSG_10,
    CAN_MSG_DUMMY,
    CAN_MATRIX_SIZE
};

void dd_can_matrix_set(uint16_t CanID, uint8_t *buff, uint16_t len );
uint16_t dd_can_matrix_get_msg_id(uint16_t msg_pos);

uint16_t dd_can_matrix_get_msg_ref(uint32_t rxId);
uint8_t * dd_can_matrix_get_msg_buff_ref(uint16_t matrix_id);

void dd_can_matrix_print();

#endif
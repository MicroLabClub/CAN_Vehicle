#include "stdint.h"
#include "stdio.h"
#include "Arduino.h"
#include "dd_can_matrix.h"

#define CAN_MESSAGE_LEN 8

typedef struct can_message_t
{
    uint32_t id;
    uint8_t message[CAN_MESSAGE_LEN];
} can_message_t;

// {ID_L, ID_H, byte0, byte1, ... byte 7}
can_message_t CanMatrix_new[CAN_MATRIX_SIZE];


char msg_string[128]; // Array to store serial string

uint8_t * dd_can_matrix_get_msg_buff_ref(uint16_t matrix_id){
    return CanMatrix_new[matrix_id].message;
}

uint16_t dd_can_matrix_get_msg_id(uint16_t msg_pos)
{
    uint16_t msg_id = CanMatrix_new[msg_pos].id;

    return msg_id;
}
    
uint16_t dd_can_matrix_get_msg_ref(uint32_t msg_id)
{
    size_t msg_ref = 0;

    msg_id &= 0x1FFFFFFF; // ignore flags

    for (size_t msg_it = 0; msg_it < CAN_MATRIX_SIZE; msg_it++)
    {
        /* code */
        if (msg_id == CanMatrix_new[msg_it].id){
            msg_ref = msg_it;
        }
    }
    
    return msg_ref;
}

void dd_can_matrix_setup(){

}

void dd_can_matrix_set(uint16_t rxId, uint8_t *rxBuf, size_t len)
{

    size_t matrixID = dd_can_matrix_get_msg_ref(rxId);
    CanMatrix_new[matrixID].id = rxId;

    for (size_t i = 0; i < len; i++)
    {
        CanMatrix_new[matrixID].message[i] = rxBuf[i];
    }
}

void dd_can_matrix_print()
{
    Serial.println("CAN Matrix report:");
    for (size_t msg_id = 0; msg_id < CAN_MATRIX_SIZE; msg_id++)
    {
        uint16_t rxId;
        rxId = CanMatrix_new[msg_id].id;

        if (rxId)
        {
            sprintf(msg_string, "Mtrx ID:[%d] ", msg_id);
            Serial.print(msg_string);

            sprintf(msg_string, "CAN ID: 0x%.4X Data:", rxId);
            Serial.print(msg_string);

            for (int i = 0; i < 8; i++)
            {
                sprintf(msg_string, " 0x%.2X", CanMatrix_new[msg_id].message[i]);
                Serial.print(msg_string);
            }
            Serial.println();
        }
    }
}


#include "stdint.h"
#include "stdio.h"
#include "Arduino.h"
#include "srv_com_can_matrix.h"

// {ID_L, ID_H, byte0, byte1, ... byte 7}
uint32_t dd_can_tx_list[TX_CAN_ID_NR_OF] = TX_CAN_ID_LIST;
uint32_t dd_can_rx_list[RX_CAN_ID_NR_OF] = RX_CAN_ID_LIST;

can_message_t dd_can_matrix[TX_CAN_MATRIX_SIZE];
can_message_t dd_can_matrix_rx[RX_CAN_MATRIX_SIZE];

char msg_string[128]; // Array to store serial string

uint32_t *ed_can_mcp_get_tx_can_list_ref()
{
    return dd_can_tx_list;
}

uint32_t *ed_can_mcp_get_rx_can_list_ref()
{
    return dd_can_rx_list;
}

can_message_t *dd_can_matrix_tx_get_msg_ref(uint16_t matrix_id)
{
    can_message_t *can_msg_ref = &dd_can_matrix[TX_CAN_MATRIX_SIZE - 1];

    for (size_t can_item = 0; can_item < TX_CAN_MATRIX_SIZE; can_item++)
    {
        if (matrix_id == dd_can_matrix[can_item].id)
        {
            can_msg_ref = &dd_can_matrix[can_item];
            break;
        }
    }

    return can_msg_ref;
}

can_message_t *dd_can_matrix_rx_get_msg_ref(uint16_t matrix_id)
{
    can_message_t *can_msg_ref = NULL;

    for (size_t can_item = 0; can_item < RX_CAN_MATRIX_SIZE; can_item++)
    {
        can_msg_ref = &dd_can_matrix_rx[can_item];
        if (matrix_id == dd_can_matrix_rx[can_item].id)
        {
            break;
        }
    }

    return can_msg_ref;
}

void dd_can_matrix_setup()
{
    // register TX Messages
    for (size_t can_item = 0; can_item < TX_CAN_ID_NR_OF; can_item++)
    {
        dd_can_matrix[can_item].id = dd_can_tx_list[can_item];
        dd_can_matrix[can_item].direction = TX_MSG; // tx
    }

    // register RX Messages
    for (size_t can_item = 0; can_item < RX_CAN_ID_NR_OF; can_item++)
    {
        dd_can_matrix_rx[can_item].id = dd_can_rx_list[can_item];
        dd_can_matrix_rx[can_item].direction = RX_MSG; // rx
    }

    dd_can_tx_matrix_print();
}

void dd_can_matrix_rx_set(uint16_t rxId, uint8_t *rxBuf, size_t len)
{
    can_message_t *can_msg_ref = dd_can_matrix_rx_get_msg_ref(rxId);

    can_msg_ref->counter++;

    for (size_t i = 0; i < len; i++)
    {
        can_msg_ref->rx_msg[i] = rxBuf[i];
    }
}

void dd_can_matrix_tx_set(uint16_t rxId, uint8_t *rxBuf, size_t len)
{
    can_message_t *can_msg_ref = dd_can_matrix_tx_get_msg_ref(rxId);

    can_msg_ref->counter++;

    for (size_t i = 0; i < len; i++)
    {
        can_msg_ref->tx_msg[i] = rxBuf[i];
    }
}

void dd_can_matrix_tx_get(uint16_t txId, uint8_t *txBuf, size_t len)
{
    can_message_t *can_msg_ref = dd_can_matrix_tx_get_msg_ref(txId);

    can_msg_ref->counter++;

    for (size_t i = 0; i < len; i++)
    {
        txBuf[i] = can_msg_ref->tx_msg[i];
    }
}

void dd_can_tx_matrix_print()
{
    Serial.println("CAN TX Matrix report:");
    for (size_t msg_id = 0; msg_id < TX_CAN_MATRIX_SIZE; msg_id++)
    {
        uint8_t msg_dir = dd_can_matrix[msg_id].direction;
        if (msg_dir == TX_MSG)
        {
            uint16_t rxId = dd_can_matrix[msg_id].id;
            uint16_t counter = dd_can_matrix[msg_id].counter;
            uint8_t direction = dd_can_matrix[msg_id].direction;

            sprintf(msg_string, "Mtrx ID:[%d] ", msg_id);
            Serial.print(msg_string);

            sprintf(msg_string, "CNT: (%4d) ", counter);
            Serial.print(msg_string);

            sprintf(msg_string, "DIR: <%d> ", direction);
            Serial.print(msg_string);

            sprintf(msg_string, "CAN ID: 0x%.4X Data:", rxId);
            Serial.print(msg_string);

            for (int i = 0; i < 8; i++)
            {
                sprintf(msg_string, " %.2X", dd_can_matrix[msg_id].tx_msg[i]);
                Serial.print(msg_string);
            }
            Serial.println();
        }
    }
}
void dd_can_rx_matrix_print()
{
    Serial.println("CAN RX Matrix report:");
    for (size_t msg_id = 0; msg_id < RX_CAN_MATRIX_SIZE; msg_id++)
    {
        uint8_t msg_dir = dd_can_matrix_rx[msg_id].direction;
        if (msg_dir == TX_MSG)
        {        uint16_t rxId = dd_can_matrix_rx[msg_id].id;
        uint16_t counter = dd_can_matrix_rx[msg_id].counter;
        uint8_t direction = dd_can_matrix_rx[msg_id].direction;

        sprintf(msg_string, "Mtrx ID:[%d] ", msg_id);
        Serial.print(msg_string);

        sprintf(msg_string, "CNT: (%4d) ", counter);
        Serial.print(msg_string);

        sprintf(msg_string, "DIR: <%d> ", direction);
        Serial.print(msg_string);

        sprintf(msg_string, "CAN ID: 0x%.4X Data:", rxId);
        Serial.print(msg_string);

        for (int i = 0; i < 8; i++)
        {
            sprintf(msg_string, " %.2X", dd_can_matrix_rx[msg_id].rx_msg[i]);
            Serial.print(msg_string);
        }
        Serial.println();
        }
    }
}

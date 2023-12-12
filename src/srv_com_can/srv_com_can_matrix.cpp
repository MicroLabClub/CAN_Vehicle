#include "stdint.h"
#include "stdio.h"
#include "Arduino.h"
#include "srv_com_can_matrix.h"

// {ID_L, ID_H, byte0, byte1, ... byte 7}
uint32_t dd_can_tx_list[TX_CAN_ID_NR_OF] = TX_CAN_ID_LIST;
uint32_t dd_can_rx_list[RX_CAN_ID_NR_OF] = RX_CAN_ID_LIST;

#define SRV_CAN_MATRIX_SIZE (TX_CAN_ID_NR_OF + RX_CAN_ID_NR_OF)

can_message_t dd_can_matrix[SRV_CAN_MATRIX_SIZE];
// can_message_t dd_can_matrix_rx[SRV_CAN_MATRIX_SIZE];

char msg_string[128]; // Array to store serial string

uint32_t *ed_can_mcp_get_tx_can_list_ref()
{
    return dd_can_tx_list;
}

uint32_t *ed_can_mcp_get_rx_can_list_ref()
{
    return dd_can_rx_list;
}

can_message_t *dd_can_matrix_get_msg_ref(uint16_t matrix_id)
{
    can_message_t *can_msg_ref = NULL;

    for (uint8_t can_item = 0; can_item < SRV_CAN_MATRIX_SIZE; can_item++)
    {
        if (matrix_id == dd_can_matrix[can_item].id)
        {
            can_msg_ref = &dd_can_matrix[can_item];
            break;
        }
    }

    return can_msg_ref;
}

// can_message_t *dd_can_matrix_get_msg_ref(uint16_t matrix_id)
// {
//     can_message_t *can_msg_ref = NULL;

//     for (uint8_t can_item = 0; can_item < SRV_CAN_MATRIX_SIZE; can_item++)
//     {
//         can_msg_ref = &dd_can_matrix[can_item];
//         if (matrix_id == dd_can_matrix[can_item].id)
//         {
//             break;
//         }
//     }

//     return can_msg_ref;
// }

void dd_can_matrix_setup()
{

    // register RX Messages
    for (uint8_t can_item = 0; can_item < RX_CAN_ID_NR_OF; can_item++)
    {
        dd_can_matrix[can_item].id = dd_can_rx_list[can_item];
        dd_can_matrix[can_item].direction = RX_MSG; // rx
    }

    // register TX Messages
    for (uint8_t can_item = 0 + RX_CAN_ID_NR_OF; can_item < TX_CAN_ID_NR_OF+RX_CAN_ID_NR_OF; can_item++)
    {
        dd_can_matrix[can_item].id = dd_can_tx_list[can_item];
        dd_can_matrix[can_item].direction = TX_MSG; // tx
    }
}

void dd_can_matrix_rx_set(uint16_t rxId, uint8_t *rxBuf, size_t len)
{
    can_message_t *can_msg_ref = dd_can_matrix_get_msg_ref(rxId);

    if (can_msg_ref != NULL)
    {
        can_msg_ref->rx_counter++;

        for (uint8_t i = 0; i < len; i++)
        {
            can_msg_ref->rx_msg[i] = rxBuf[i];
        }
    }
}

void dd_can_matrix_tx_set(uint16_t rxId, uint8_t *rxBuf, size_t len)
{
    can_message_t *can_msg_ref = dd_can_matrix_get_msg_ref(rxId);

    if (can_msg_ref != NULL)
    {
        can_msg_ref->tx_counter++;

        for (uint8_t i = 0; i < len; i++)
        {
            can_msg_ref->tx_msg[i] = rxBuf[i];
        }
    }
}

void dd_can_matrix_tx_get(uint16_t txId, uint8_t *txBuf, size_t len)
{
    can_message_t *can_msg_ref = dd_can_matrix_get_msg_ref(txId);

    if (can_msg_ref != NULL)
    {
        for (uint8_t i = 0; i < len; i++)
        {
            txBuf[i] = can_msg_ref->tx_msg[i];
        }
    }
}

void dd_can_matrix_print()
{
    Serial.println("CAN TX Matrix report:");
    for (uint8_t msg_id = 0; msg_id < SRV_CAN_MATRIX_SIZE; msg_id++)
    {
        uint16_t rxId = dd_can_matrix[msg_id].id;
        uint16_t tx_counter = dd_can_matrix[msg_id].tx_counter;
        uint16_t rx_counter = dd_can_matrix[msg_id].rx_counter;
        uint8_t direction = dd_can_matrix[msg_id].direction;

        sprintf(msg_string, "Mtrx ID:[%d] ", msg_id);
        Serial.print(msg_string);

        sprintf(msg_string, "CNT: (%4d/%4d) ", tx_counter, rx_counter);
        Serial.print(msg_string);

        if (direction == TX_MSG)
        {
            sprintf(msg_string, "DIR:TX ");
        }
        else
        {
            sprintf(msg_string, "DIR:RX ");
        }
        Serial.print(msg_string);

        sprintf(msg_string, "ID: 0x%.4X", rxId);
        Serial.print(msg_string);

        sprintf(msg_string, " TXD:");
        Serial.print(msg_string);

        for (int i = 0; i < 8; i++)
        {
            sprintf(msg_string, " %.2X", dd_can_matrix[msg_id].tx_msg[i]);
            Serial.print(msg_string);
        }
        sprintf(msg_string, " - RXD:");
        Serial.print(msg_string);

        for (int i = 0; i < 8; i++)
        {
            sprintf(msg_string, " %.2X", dd_can_matrix[msg_id].rx_msg[i]);
            Serial.print(msg_string);
        }

        Serial.println();
    }
}

#ifndef ED_CAN_MCP_H_
#define ED_CAN_MCP_H_

#include "ecu_config.h"
#include "stdint.h"

#ifndef CAN0_INT 
#define CAN0_INT 2 // Set INT to pin 2
#endif

#ifndef CAN0_CS
#define CAN0_CS 10 // Set CS to pin 2
#endif

void dd_can_setup();
void dd_can_recv_loop();
void dd_can_send_loop();
void dd_can_tx_buff_print();
void dd_can_rx_buff_print();
void dd_can_buff_print(uint16_t can_id, uint8_t* can_data);

#endif
#ifndef DD_MCP_CAN_H_
#define DD_MCP_CAN_H_
#include "dd_can_matrix.h"


#define CAN0_INT 2 // Set INT to pin 2
#define CAN0_CS 8 // Set CS to pin 2

void dd_can_setup();
void dd_can_recv_loop();
void dd_can_send_loop();
void dd_can_tx_buff_print();


#endif
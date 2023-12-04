#ifndef DD_SIGNAL_H_
#define DD_SIGNAL_H_
#include "stdint.h"
#include "srv_com_can_matrix.h"

#include "ecu_config.h"


void dd_can_signal_loop();


#ifdef CAN_ID_JOYSTICK
void dd_can_signal_set_joistick();
#endif

#ifdef CAN_ID_UI_BT
void dd_can_signal_set_ui_bt();
uint8_t dd_can_signal_get_ui_bt( uint8_t key_id);
#endif

uint8_t dd_can_signal_get_bip();
uint16_t dd_can_signal_get_x();
uint16_t dd_can_signal_get_y();


#endif


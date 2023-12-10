#ifndef DD_SIGNAL_H_
#define DD_SIGNAL_H_
#include "stdint.h"
#include "srv_com_can_matrix.h"

#include "ecu_config.h"


void dd_can_signal_loop();


void dd_can_signal_set_joistick();

void dd_can_signal_set_ui_bt();
uint8_t dd_can_signal_get_ui_bt( uint8_t key_id);
void dd_can_signal_set_bt_ui_chassis();
uint16_t dd_can_signal_get_bt_ui_power();
uint16_t dd_can_signal_get_bt_ui_steering();

uint8_t dd_can_signal_get_bip();
uint16_t dd_can_signal_get_x();
uint16_t dd_can_signal_get_y();


#endif


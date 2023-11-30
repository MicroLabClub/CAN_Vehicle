#ifndef DD_SIGNAL_H_
#define DD_SIGNAL_H_
#include "stdint.h"
#include "dd_can_matrix.h"



void dd_can_signal_loop();


#ifdef CAN_ID_JOYSTICK
void dd_can_signal_set_joistick();
#endif

#ifdef CAN_ID_ROMAN_A
uint8_t dd_can_signal_get_bip();
#endif


#endif


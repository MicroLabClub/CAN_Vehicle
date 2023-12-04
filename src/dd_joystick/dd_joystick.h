
#ifndef DD_JOYSTICK_H_
#define DD_JOYSTICK_H_

// Joystick PinMap
#define DD_JOYSTICK_X A0
#define DD_JOYSTICK_Y A1
#define DD_JOYSTICK_B A2



#include "stdint.h"

#include "ecu_config.h"

void dd_joystick_setup();
void dd_joystick_loop();
uint16_t dd_joystick_get_x();
uint16_t dd_joystick_get_y();
uint8_t dd_joystick_get_b();

void dd_joystick_report();

#endif

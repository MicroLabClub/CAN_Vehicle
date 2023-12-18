#ifndef CTRL_STEERING_H
#define CTRL_STEERING_H
#include "ecu_config.h"

// Include any necessary headers here

// Define any constants or macros here

#define CTRL_STEERING_TARGET_MODE_CAN 0
#define CTRL_STEERING_TARGET_MODE_BT 1
#define CTRL_STEERING_TARGET_MODE_MANUAL 2

#ifndef CTRL_STEERING_TARGET_MODE
#define CTRL_STEERING_TARGET_MODE CTRL_STEERING_TARGET_MODE_MANUAL
#endif

#define CTRL_STEERING_FB_MODE_ENCODER 0
#define CTRL_STEERING_FB_MODE_POTENTIOMETER 1
#define CTRL_STEERING_FB_MODE_TIMER 2

#ifndef CTRL_STEERING_FB_MODE
#define CTRL_STEERING_FB_MODE CTRL_STEERING_FB_MODE_TIMER
#endif

#define CTRL_STEERING_OP_MODE_STEP 0
#define CTRL_STEERING_OP_MODE_CONTINUOUS 1
#define CTRL_STEERING_OP_MODE_POWER 2

#ifndef CTRL_STEERING_OP_MODE
#define CTRL_STEERING_OP_MODE CTRL_STEERING_OP_MODE_STEP
#endif

#define CTRL_STEERING_DISABLE 0
#define CTRL_STEERING_ENABLE 1

#ifndef CTRL_STEERING_MODE
#define CTRL_STEERING_MODE CTRL_STEERING_ENABLE
#endif

#ifndef CTRL_STEERING_POWER
#define CTRL_STEERING_POWER 255
#endif

// Declare any function prototypes here

int8_t ctrl_steering_enable();
int8_t ctrl_steering_disable();
int8_t ctrl_steering_is_enabled();
uint8_t ctrl_steering_set_target_mode(uint8_t mode);
uint8_t ctrl_steering_get_target_mode();
uint8_t ctrl_steering_set_fb_mode(uint8_t mode);
uint8_t ctrl_steering_get_fb_mode();

int16_t ctrl_steering_get_power();
int16_t ctrl_steering_set_power(int16_t power);
int16_t ctrl_steering_power_up(int16_t power);
int16_t ctrl_steering_power_down(int16_t power);

int16_t ctrl_steering_get_target_angle();
int16_t ctrl_steering_set_target_angle(int16_t angle);
int16_t ctrl_steering_get_current_angle();
int16_t ctrl_steering_set_current_angle(int16_t angle);

int16_t ctrl_steering_turn_right(int16_t angle);
int16_t ctrl_steering_turn_left(int16_t angle);

void ctrl_steering_setup();
void ctrl_steering_loop();

#endif // CTRL_STEERING_H

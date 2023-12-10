#ifndef CTRL_STEERING_H
#define CTRL_STEERING_H

// Include any necessary headers here

// Define any constants or macros here

// Declare any function prototypes here
void ctrl_steering_setup();
void ctrl_steering_loop();

int16_t ctrl_steering_get_angle();
int16_t ctrl_steering_set_angle(int16_t angle);
int8_t ctrl_steering_enable();
int8_t ctrl_steering_disable();
int8_t ctrl_steering_is_enable();

#endif // CTRL_STEERING_H

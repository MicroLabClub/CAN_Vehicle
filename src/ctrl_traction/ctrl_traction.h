#ifndef CTRL_TRACTION_H
#define CTRL_TRACTION_H

// Include any necessary headers here

// Define any constants or macros here

// Declare any function prototypes here
void ctrl_traction_setup();
void ctrl_traction_loop();

int16_t ctrl_traction_get_power();
int16_t ctrl_traction_set_power(int16_t power);
int8_t ctrl_traction_enable();
int8_t ctrl_traction_disable();
int8_t ctrl_traction_is_enable();

#endif // CTRL_TRACTION_H

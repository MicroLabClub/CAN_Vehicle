#ifndef DD_ENCODER_H_
#define DD_ENCODER_H_

 #define DD_ENCODER_PH_A A2
 #define DD_ENCODER_PH_B A3

 #include "stdint.h"

void dd_encoder_setup();
void dd_encoder_loop();

int16_t  dd_encoder_get_counter();
int16_t  dd_encoder_set_counter(int16_t cnt);
int16_t  dd_encoder_reset_counter();

void dd_encoder_report();

#endif


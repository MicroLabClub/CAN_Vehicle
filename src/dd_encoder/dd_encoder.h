#ifndef DD_ENCODER_H_
#define DD_ENCODER_H_

 #define DD_ENCODER_PH_A 4
 #define DD_ENCODER_PH_B 5

 #include "stdint.h"

void dd_encoder_setup();
void dd_encoder_loop();

uint16_t  dd_encoder_get_counter();
uint16_t  dd_encoder_set_counter(uint16_t cnt);
uint16_t  dd_encoder_reset_counter();

void dd_encoder_report();

#endif


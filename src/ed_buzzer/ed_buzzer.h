#ifndef ED_BUZZER_H_
#define ED_BUZZER_H_
#include "stdint.h"

#include "ecu_config.h"

#ifndef ED_BUZZER_PIN
#define ED_BUZZER_PIN A6
#endif

#define ED_BUZZER_OFF LOW
#define ED_BUZZER_ON HIGH

void ed_buzzer_setup();
void ed_buzzer_loop();
uint8_t ed_buzzer_get_state( );
void ed_buzzer_set_state(uint8_t state);
void ed_buzzer_on();
void ed_buzzer_off();


#endif

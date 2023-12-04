#include "ed_buzzer.h"
#include "Arduino.h"
uint8_t ed_buzzer_state = 0;

void ed_buzzer_setup(){
    pinMode(ED_BUZZER_PIN, OUTPUT);
    ed_buzzer_state = 0;
}

uint8_t ed_buzzer_get_state(){
    return ed_buzzer_state;
}

void ed_buzzer_set_state(uint8_t state){
    ed_buzzer_state = state;
}
void ed_buzzer_on(){
    ed_buzzer_set_state(ED_BUZZER_ON);
}
void ed_buzzer_off(){
        ed_buzzer_set_state(ED_BUZZER_OFF);
}


void ed_buzzer_loop(){
    uint8_t state = ed_buzzer_get_state();
    digitalWrite(ED_BUZZER_PIN, state);
}




#include "ed_l298.h"

#include "Arduino.h"

uint8_t ed_l298_in_1_pin_list[ED_L298_NR_OF] = ED_L298_IN_1_PIN_LIST;
uint8_t ed_l298_in_2_pin_list[ED_L298_NR_OF] = ED_L298_IN_2_PIN_LIST;
uint8_t ed_l298_en_pin_list[ED_L298_NR_OF] = ED_L298_EN_PIN_LIST;

ed_l298_t ed_l298_list[ED_L298_NR_OF];


void ed_l298_setup() {
    // Setup the drivers
    for (uint8_t driver_id = 0; driver_id < ED_L298_NR_OF; driver_id++) {
        ed_l298_set(driver_id, LOW, LOW, 0);

        pinMode(ed_l298_in_1_pin_list[driver_id], OUTPUT);
        pinMode(ed_l298_in_2_pin_list[driver_id], OUTPUT);
        pinMode(ed_l298_en_pin_list[driver_id],   OUTPUT);
    }
}

void ed_l298_loop() {
    //Loop the drivers
    for (uint8_t driver_id = 0; driver_id < ED_L298_NR_OF; driver_id++) {
        digitalWrite(ed_l298_in_1_pin_list[driver_id], ed_l298_list[driver_id].in_1);
        digitalWrite(ed_l298_in_2_pin_list[driver_id], ed_l298_list[driver_id].in_2);
        analogWrite(ed_l298_en_pin_list[driver_id],   ed_l298_list[driver_id].en);
    }
}

ed_l298_t* ed_l298_get_ref(uint8_t driver_id) {
    return &ed_l298_list[driver_id];
}

void ed_l298_set_in1(uint8_t driver_id, uint8_t in1) {
    ed_l298_list[driver_id].in_1 = in1;
}
 
void ed_l298_set_in2(uint8_t driver_id, uint8_t in2) {
    ed_l298_list[driver_id].in_2 = in2;
}

void ed_l298_set_en(uint8_t driver_id, uint16_t en) {
    ed_l298_list[driver_id].en = en;
}

void ed_l298_set(uint8_t driver_id, uint8_t in1, uint8_t in2, uint16_t en) {

    ed_l298_list[driver_id].in_1 = in1;
    ed_l298_list[driver_id].in_2 = in2;
    ed_l298_list[driver_id].en = en;


}


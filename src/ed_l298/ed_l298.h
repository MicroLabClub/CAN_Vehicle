
#ifndef ED_DRIVER_H
#define ED_DRIVER_H
#include "stdint.h"
#include "ecu_config.h"

typedef struct ed_l298{
    uint8_t in_1;
    uint8_t in_2;
    uint16_t en;
} ed_l298_t;

#ifndef ED_L298_IN_1_PIN_LIST
#define ED_L298_IN_1_PIN_LIST { 7}
#endif
#ifndef ED_L298_IN_2_PIN_LIST
#define ED_L298_IN_2_PIN_LIST { 8}
#endif
#ifndef ED_L298_EN_PIN_LIST
#define ED_L298_EN_PIN_LIST { 9}
#endif

enum dd_driver_id_t{
    ED_L298_ID_1,
    ED_L298_ID_2,
    ED_L298_NR_OF 
};


void ed_l298_set_in1(uint8_t driver_id, uint8_t in1);
void ed_l298_set_in2(uint8_t driver_id, uint8_t in2);
void ed_l298_set_en(uint8_t driver_id, uint16_t en);
void ed_l298_set(uint8_t driver_id, uint8_t in1, uint8_t in2, uint16_t en);
ed_l298_t* ed_l298_get_ref(uint8_t driver_id);


void ed_l298_setup();
void ed_l298_loop();

void ed_l298_report(uint8_t driver_id);


#endif // ED_DRIVER_H

#ifndef DD_DC_MOTOR_H
#define DD_DC_MOTOR_H

#include "stdint.h"
#include "ecu_config.h"

#define DD_DC_MOTOR_DRIVER_ID_LIST {ED_L298_ID_1}

#ifndef DD_DC_MOTOR_MAX_POWER
#define DD_DC_MOTOR_MAX_POWER 255
#endif
#ifndef DD_DC_MOTOR_MIN_POWER
#define DD_DC_MOTOR_MIN_POWER -255
#endif

enum dd_dc_motor_id_t{
    DD_DC_MOTOR_ID_1,
    DD_DC_MOTOR_ID_2,
    DD_DC_MOTOR_NR_OF
};

int16_t dd_dc_motor_set_power(uint8_t motor_id, int16_t power);
int16_t dd_dc_motor_get_power(uint8_t motor_id);
 
 void dd_dc_motor_loop();
 void dd_dc_motor_setup();


#endif // DD_DC_MOTOR_H

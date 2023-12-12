#include "Arduino.h"
#include "dd_dc_motor.h"
#include "ed_l298/ed_l298.h"
#include "stdint.h"

uint8_t dd_motor_driver_id[DD_DC_MOTOR_NR_OF] = DD_DC_MOTOR_DRIVER_ID_LIST;
int16_t dd_motor_power[DD_DC_MOTOR_NR_OF] = {0};

void dd_dc_motor_setup()
{
    for (uint8_t i = 0; i < DD_DC_MOTOR_NR_OF; i++)
    {
        dd_dc_motor_set_power(i, 0);
    }

}

void dd_dc_motor_loop()
{
    for (uint8_t i = 0; i < DD_DC_MOTOR_NR_OF; i++)
    {
        int16_t motor_power = dd_dc_motor_get_power(i);
        if (motor_power > 0)
        {
            ed_l298_set(i, HIGH, LOW, motor_power);
        }
        else if (motor_power < 0)
        {
            ed_l298_set(i, LOW, HIGH, -motor_power);
        }
        else
        {
            ed_l298_set(i, LOW, LOW, 0);
        }
        // ed_l298_set(dd_motor_driver_id[i],
        //             dd_motor_power[i] > 0,
        //             dd_motor_power[i] < 0,
        //             abs(dd_motor_power[i])
        //        );
    }
}

int16_t dd_dc_motor_get_power(uint8_t motor_id)
{
    return dd_motor_power[motor_id];
}

int16_t dd_dc_motor_set_power(uint8_t motor_id, int16_t power)
{
    if (power > DD_DC_MOTOR_MAX_POWER)
    {
        power = DD_DC_MOTOR_MAX_POWER;
    }
    if (power < DD_DC_MOTOR_MIN_POWER)
    {
        power = DD_DC_MOTOR_MIN_POWER;
    }
    dd_motor_power[motor_id] = power;
    return dd_motor_power[motor_id];
}

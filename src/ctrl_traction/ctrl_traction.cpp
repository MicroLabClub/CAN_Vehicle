#include "Arduino.h"
#include "ctrl_traction.h"
#include "ecu_config.h"
#include "srv_com_can/srv_com_can_signal.h"
#include "ed_l298/ed_l298.h"
#include "dd_dc_motor/dd_dc_motor.h"

int16_t ctrl_traction_power = 0;
int8_t ctrl_traction_mode = 0;

void ctrl_traction_setup()
{
    ctrl_traction_set_power(0);
}

int16_t ctrl_traction_get_power()
{
    return ctrl_traction_power;
}
int16_t ctrl_traction_set_power(int16_t power)
{
    if (power > DD_DC_MOTOR_MAX_POWER)
    {
        power = DD_DC_MOTOR_MAX_POWER;
    }
    else if (power < DD_DC_MOTOR_MIN_POWER)
    {
        power = DD_DC_MOTOR_MIN_POWER;
    }
    ctrl_traction_power = power;
    return ctrl_traction_power;
}
int8_t ctrl_traction_enable()
{
    ctrl_traction_mode = 1;
    return ctrl_traction_mode;
}
int8_t ctrl_traction_disable()
{
    ctrl_traction_mode = 0;
    return ctrl_traction_mode;
}
int8_t ctrl_traction_is_enable()
{
    return ctrl_traction_mode;
}

int16_t ctrl_traction_power_up(int16_t power)
{
    power = ctrl_traction_get_power() + power;
    power = ctrl_traction_set_power(power);
    return power;
}

int16_t ctrl_traction_power_down(int16_t power)
{
    power = ctrl_traction_get_power() - power;
    power = ctrl_traction_set_power(power);
    return power;
}

void ctrl_traction_loop()
{
    int16_t traction_power;

    if (ctrl_traction_is_enable())
    {
        traction_power = dd_can_signal_get_bt_ui_power() * 2;
        ctrl_traction_set_power(traction_power);
    }
    else
    {
        traction_power = ctrl_traction_get_power();
    }


    dd_dc_motor_set_power(DD_DC_MOTOR_ID_1, traction_power);

    // Serial.println(traction_power);
    // if(traction_power > 0){
    //     ed_l298_set(ED_L298_ID_1, HIGH, LOW, traction_power);
    // }else if(traction_power < 0){
    //     ed_l298_set(ED_L298_ID_1, LOW, HIGH, -traction_power);
    // }else{
    //     ed_l298_set(ED_L298_ID_1, LOW, LOW, 0);
    // }
}
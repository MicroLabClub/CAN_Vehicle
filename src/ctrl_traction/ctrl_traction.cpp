#include "Arduino.h"
#include "ctrl_traction.h"
#include "srv_com_can/srv_com_can_signal.h"
#include "srv_ui_bt/srv_ui_bt.h"
#include "ed_l298/ed_l298.h"
#include "dd_dc_motor/dd_dc_motor.h"
#include "dd_encoder/dd_encoder.h"

uint8_t ctrl_traction_target_mode = CTRL_TRACTION_TARGET_MODE_CAN;
uint8_t ctrl_traction_fb_mode = CTRL_TRACTION_FB_MODE_ENCODER;
uint8_t ctrl_traction_op_mode = CTRL_TRACTION_OP_MODE;
int16_t ctrl_traction_target_step = 0;
int16_t ctrl_traction_current_step = 0;

int16_t ctrl_traction_power = 0;
int8_t ctrl_traction_enable_state = 0;

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

int16_t ctrl_traction_get_target_step()
{
    return ctrl_traction_target_step;
}

int16_t ctrl_traction_set_target_step(int16_t step)
{

    ctrl_traction_target_step = step;
    return ctrl_traction_target_step;
}
int16_t ctrl_traction_get_current_step()
{
    return ctrl_traction_current_step;
}
int16_t ctrl_traction_set_current_step(int16_t step)
{

    ctrl_traction_current_step = step;
    return ctrl_traction_current_step;
}

int16_t ctrl_traction_step_up(int16_t step)
{
    step = ctrl_traction_get_target_step() + step;
    step = ctrl_traction_set_target_step(step);
    return step;
}
int16_t ctrl_traction_step_down(int16_t step)
{
    step = ctrl_traction_get_target_step() - step;
    step = ctrl_traction_set_target_step(step);
    return step;
}

int8_t ctrl_traction_enable()
{
    ctrl_traction_enable_state = 1;
    return ctrl_traction_enable_state;
}
int8_t ctrl_traction_disable()
{
    ctrl_traction_enable_state = 0;
    return ctrl_traction_enable_state;
}
int8_t ctrl_traction_is_enabled()
{
    return ctrl_traction_enable_state;
}

uint8_t ctrl_traction_set_mode(uint8_t mode)
{
    ctrl_traction_enable_state = mode;
    return ctrl_traction_enable_state;
}

uint8_t ctrl_traction_set_target_mode(uint8_t mode)
{
    ctrl_traction_target_mode = mode;
    return ctrl_traction_target_mode;
}
uint8_t ctrl_traction_get_target_mode()
{
    return ctrl_traction_target_mode;
}
uint8_t ctrl_traction_set_fb_mode(uint8_t mode)
{
    ctrl_traction_fb_mode = mode;
    return ctrl_traction_fb_mode;
}
uint8_t ctrl_traction_get_fb_mode()
{
    return ctrl_traction_fb_mode;
}
uint8_t ctrl_traction_set_op_mode(uint8_t mode)
{
    ctrl_traction_op_mode = mode;
    return ctrl_traction_op_mode;
}
uint8_t ctrl_traction_get_op_mode()
{
    return ctrl_traction_op_mode;
}
uint8_t ctrl_traction_is_step_mode()
{
    return ctrl_traction_op_mode == CTRL_TRACTION_OP_MODE_STEP;
}
void ctrl_traction_setup()
{
    ctrl_traction_set_target_step(0);
    ctrl_traction_set_current_step(0);

    ctrl_traction_set_mode(CTRL_TRACTION_MODE);
    ctrl_traction_set_target_mode(CTRL_TRACTION_TARGET_MODE);
    ctrl_traction_set_fb_mode(CTRL_TRACTION_FB_MODE);
    ctrl_traction_set_op_mode(CTRL_TRACTION_OP_MODE);
    ctrl_traction_set_power(0);
}

void ctrl_traction_loop()
{
    int16_t traction_power;

    int16_t target_step;
    int16_t current_step;

    if (ctrl_traction_is_enabled())
    {
        if (ctrl_traction_fb_mode == CTRL_TRACTION_FB_MODE_ENCODER)
        {
            current_step = dd_encoder_get_counter();
            ctrl_traction_current_step = current_step;
        }
        // else if(ctrl_traction_fb_mode == CTRL_TRACTION_FB_MODE_POTENTIOMETER)
        // {
        //     current_step = dd_can_signal_get_potentiometer_traction() * 2;
        //     ctrl_traction_current_step = current_step;
        // }
        else if (ctrl_traction_fb_mode == CTRL_TRACTION_FB_MODE_TIMER)
        {
            if (ctrl_traction_current_step > ctrl_traction_target_step)
            {
                ctrl_traction_current_step--;
            }
            else if (ctrl_traction_current_step < ctrl_traction_target_step)
            {
                ctrl_traction_current_step++;
            }
            else
            {
                ctrl_traction_current_step = ctrl_traction_target_step;
            }
        }

        current_step = ctrl_traction_current_step;
        ctrl_traction_set_current_step(current_step);

        if (ctrl_traction_target_mode == CTRL_TRACTION_TARGET_MODE_CAN)
        {
            if (ctrl_traction_op_mode == CTRL_TRACTION_OP_MODE_STEP)
            {
                target_step = dd_can_signal_get_bt_ui_steering() * 2;
                ctrl_traction_set_target_step(traction_power);
            }
            else{
                traction_power = dd_can_signal_get_bt_ui_power() * 2;
            }
        }
        else if (ctrl_traction_target_mode == CTRL_TRACTION_TARGET_MODE_BT)
        {
            traction_power = srv_ui_bt_get_power()*2;
            ctrl_traction_set_power(traction_power);
        }

        else if (ctrl_traction_target_mode == CTRL_TRACTION_TARGET_MODE_MANUAL)
        {
            traction_power = ctrl_traction_get_power();
        }

        ctrl_traction_set_target_step(target_step);
        ctrl_traction_set_power(traction_power);

        if (ctrl_traction_op_mode == CTRL_TRACTION_OP_MODE_STEP)
        {   
            traction_power = ctrl_traction_set_power(255);

            if (target_step > current_step)
            {
                dd_dc_motor_set_power(DD_DC_MOTOR_ID_2, ctrl_traction_power);
            }
            else if (target_step < current_step)
            {
                dd_dc_motor_set_power(DD_DC_MOTOR_ID_2, -ctrl_traction_power);
            }
            else
            {
                dd_dc_motor_set_power(DD_DC_MOTOR_ID_2, 0);
            }
        }
        else if (ctrl_traction_op_mode == CTRL_TRACTION_OP_MODE_CONTINUOUS)
        {
            traction_power = ctrl_traction_get_power();
            dd_dc_motor_set_power(DD_DC_MOTOR_ID_2, traction_power);
        }
        else if (ctrl_traction_op_mode == CTRL_TRACTION_OP_MODE_POWER)
        {
            traction_power = ctrl_traction_get_power();
            dd_dc_motor_set_power(DD_DC_MOTOR_ID_2, traction_power);
        }
        //     traction_power = ctrl_traction_get_power();

        // dd_dc_motor_set_power(DD_DC_MOTOR_ID_1, traction_power);
    }
    else
    {
        traction_power = ctrl_traction_get_power();
        dd_dc_motor_set_power(DD_DC_MOTOR_ID_2, 0);
    }
}
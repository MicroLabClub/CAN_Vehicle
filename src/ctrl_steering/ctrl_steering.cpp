#include "Arduino.h"
#include "ctrl_steering.h"
#include "srv_com_can/srv_com_can_signal.h"
#include "srv_ui_bt/srv_ui_bt.h"
#include "dd_dc_motor/dd_dc_motor.h"
#include "dd_encoder/dd_encoder.h"
#include "ed_l298/ed_l298.h"

#define CTRL_STEERING_ANGLE_MAX (10000)
#define CTRL_STEERING_ANGLE_MIN (-10000)

uint8_t ctrl_steering_target_mode = CTRL_STEERING_TARGET_MODE;
uint8_t ctrl_steering_fb_mode = CTRL_STEERING_FB_MODE;
uint8_t ctrl_steering_op_mode = CTRL_STEERING_OP_MODE;
int16_t ctrl_steering_target_angle = 0;
int16_t ctrl_steering_current_angle = 0;
int16_t ctrl_steering_power = 0;
int8_t ctrl_steering_enable_state = CTRL_STEERING_MODE;

int16_t ctrl_steering_get_power()
{
    return ctrl_steering_power;
}
int16_t ctrl_steering_set_power(int16_t power)
{
    if (power > DD_DC_MOTOR_MAX_POWER)
    {
        power = DD_DC_MOTOR_MAX_POWER;
    }
    else if (power < 0)
    {
        power = 0;
    }
    ctrl_steering_power = power;
    return ctrl_steering_power;
}

int16_t ctrl_steering_power_up(int16_t power)
{
    power = ctrl_steering_get_power() + power;
    power = ctrl_steering_set_power(power);
    return power;
}

int16_t ctrl_steering_power_down(int16_t power)
{
    power = ctrl_steering_get_power() - power;
    power = ctrl_steering_set_power(power);
    return power;
}

int16_t ctrl_steering_get_target_angle()
{
    return ctrl_steering_target_angle;
}

int16_t ctrl_steering_set_target_angle(int16_t angle)
{
    if (angle > CTRL_STEERING_ANGLE_MAX)
    {
        angle = CTRL_STEERING_ANGLE_MAX;
    }
    else if (angle < CTRL_STEERING_ANGLE_MIN)
    {
        angle = CTRL_STEERING_ANGLE_MIN;
    }
    ctrl_steering_target_angle = angle;
    return ctrl_steering_target_angle;
}
int16_t ctrl_steering_get_current_angle()
{
    return ctrl_steering_current_angle;
}
int16_t ctrl_steering_set_current_angle(int16_t angle)
{
    if (angle > CTRL_STEERING_ANGLE_MAX)
    {
        angle = CTRL_STEERING_ANGLE_MAX;
    }
    else if (angle < CTRL_STEERING_ANGLE_MIN)
    {
        angle = CTRL_STEERING_ANGLE_MIN;
    }
    ctrl_steering_current_angle = angle;
    return ctrl_steering_current_angle;
}

int16_t ctrl_steering_turn_right(int16_t angle)
{
    angle = ctrl_steering_get_target_angle() + angle;
    angle = ctrl_steering_set_target_angle(angle);
    return angle;
}
int16_t ctrl_steering_turn_left(int16_t angle)
{
    angle = ctrl_steering_get_target_angle() - angle;
    angle = ctrl_steering_set_target_angle(angle);
    return angle;
}

int8_t ctrl_steering_enable()
{
    ctrl_steering_enable_state = 1;
    return ctrl_steering_enable_state;
}
int8_t ctrl_steering_disable()
{
    ctrl_steering_enable_state = 0;
    return ctrl_steering_enable_state;
}
int8_t ctrl_steering_is_enabled()
{
    return ctrl_steering_enable_state;
}

uint8_t ctrl_steering_set_mode(uint8_t mode)
{
    ctrl_steering_enable_state = mode;
    return ctrl_steering_enable_state;
}

uint8_t ctrl_steering_set_target_mode(uint8_t mode)
{
    ctrl_steering_target_mode = mode;
    return ctrl_steering_target_mode;
}
uint8_t ctrl_steering_get_target_mode()
{
    return ctrl_steering_target_mode;
}
uint8_t ctrl_steering_set_fb_mode(uint8_t mode)
{
    ctrl_steering_fb_mode = mode;
    return ctrl_steering_fb_mode;
}
uint8_t ctrl_steering_get_fb_mode()
{
    return ctrl_steering_fb_mode;
}

void ctrl_steering_setup()
{
    ctrl_steering_set_target_angle(0);
    ctrl_steering_set_current_angle(0);

    ctrl_steering_set_mode(CTRL_STEERING_MODE);
    ctrl_steering_set_target_mode(CTRL_STEERING_TARGET_MODE);
    ctrl_steering_set_fb_mode(CTRL_STEERING_FB_MODE);
    ctrl_steering_set_power(CTRL_STEERING_POWER);
}

void ctrl_steering_loop()
{
    int16_t steering_power;
    int16_t target_angle;
    int16_t current_angle;

    if (ctrl_steering_is_enabled())
    {
        if (ctrl_steering_fb_mode == CTRL_STEERING_FB_MODE_ENCODER)
        {
            current_angle = dd_encoder_get_counter();
            ctrl_steering_current_angle = current_angle;
        }
        // else if(ctrl_steering_fb_mode == CTRL_STEERING_FB_MODE_POTENTIOMETER)
        // {
        //     current_angle = dd_can_signal_get_potentiometer_steering() * 2;
        //     ctrl_steering_current_angle = current_angle;
        // }
        else if (ctrl_steering_fb_mode == CTRL_STEERING_FB_MODE_TIMER)
        {
            if (ctrl_steering_current_angle > ctrl_steering_target_angle)
            {
                ctrl_steering_current_angle--;
            }
            else if (ctrl_steering_current_angle < ctrl_steering_target_angle)
            {
                ctrl_steering_current_angle++;
            }
            else
            {
                ctrl_steering_current_angle = ctrl_steering_target_angle;
            }
        }

        current_angle = ctrl_steering_current_angle;
        ctrl_steering_set_current_angle(current_angle);

        if (ctrl_steering_target_mode == CTRL_STEERING_TARGET_MODE_CAN)
        {
            target_angle = dd_can_signal_get_bt_ui_steering();
            ctrl_steering_set_target_angle(target_angle);
        }
        else if (ctrl_steering_target_mode == CTRL_STEERING_TARGET_MODE_BT)
        {
            target_angle = srv_ui_bt_get_steering();
            ctrl_steering_set_target_angle(target_angle);
        }
        else if (ctrl_steering_target_mode == CTRL_STEERING_TARGET_MODE_MANUAL)
        {
            target_angle = ctrl_steering_get_target_angle();
        }

        ctrl_steering_set_target_angle(target_angle);

        if (target_angle > current_angle)
        {
            dd_dc_motor_set_power(DD_DC_MOTOR_ID_1, ctrl_steering_power);
        }
        else if (target_angle < current_angle)
        {
            dd_dc_motor_set_power(DD_DC_MOTOR_ID_1, -ctrl_steering_power);
        }
        else
        {
            dd_dc_motor_set_power(DD_DC_MOTOR_ID_1, 0);
        }
    }
    else
    {
        steering_power = ctrl_steering_get_power();
        dd_dc_motor_set_power(DD_DC_MOTOR_ID_2, 0);
    }

}
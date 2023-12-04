#include "srv_control.h"
#include "stdint.h"
#include "srv_com_can/srv_com_can_signal.h"
#include "ed_buzzer/ed_buzzer.h"

#include "Arduino.h"

void srv_control_setup()
{
}

void srv_control_loop()
{

    uint8_t bip_sig = dd_can_signal_get_bip();
    
    if (bip_sig == 0x00)
    {
        ed_buzzer_set_state(1);
    }
    else
    {
        ed_buzzer_set_state(0);
    }
}
#include "Arduino.h"
#include "ctrl_steering.h"
#include "ecu_config.h"
#include "srv_com_can/srv_com_can_signal.h"
#include "ed_l298/ed_l298.h"

void ctrl_steering_setup(){

}

int16_t ctrl_steering_angle = 0;

int16_t ctrl_steering_get_angle(){
    return ctrl_steering_angle;
}
int16_t ctrl_steering_set_angle(int16_t angle){
    ctrl_steering_angle = angle;
    return ctrl_steering_angle;
}


void ctrl_steering_loop(){
    int16_t steering_angle = dd_can_signal_get_bt_ui_steering();
    ctrl_steering_set_angle(steering_angle);

    Serial.print(F("Steering angle: "));
    Serial.println(steering_angle);

    if(steering_angle > 0){
        ed_l298_set(ED_L298_ID_1, HIGH, LOW, steering_angle);
    }else if(steering_angle < 0){
        ed_l298_set(ED_L298_ID_1, LOW, HIGH, -steering_angle);
    }else{  
        ed_l298_set(ED_L298_ID_1, LOW, LOW, 0);
    }
}
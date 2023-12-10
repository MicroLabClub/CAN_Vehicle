#ifndef SRV_UI_SERIAL_H_
#define SRV_UI_SERIAL_H_

void srv_ui_serial_setup();
void srv_ui_serial_in_loop();
void srv_ui_serial_out_loop();

void srv_ui_serial_ctrl_steering_report();
void srv_ui_serial_ctrl_traction_report();

void srv_ui_serial_dd_motor_report();
void srv_ui_serial_ed_l298_report();

void srv_ui_serial_dd_sns_angle_report();
void srv_ui_serial_ed_pot_report();
void srv_ui_serial_ed_encoder_report();

#endif

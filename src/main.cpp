#include "Arduino.h"

#include "ecu_config.h"

//=============================================================================
// Include control modules
#ifdef USE_SRV_CONTROL
#include "srv_control/srv_control.h"
#endif

//=============================================================================
// Include platform services
#ifdef USE_SRV_UI_SERIAL
#include "srv_ui_serial/srv_ui_serial.h"
#endif
#ifdef USE_SRV_UI_LCD
#include "srv_ui_lcd/srv_ui_lcd.h"
#endif
#ifdef USE_SRV_UI_BT
#include "srv_ui_bt/srv_ui_bt.h"
#endif
#ifdef USE_SRV_COM_CAN
#include "srv_com_can/srv_com_can_matrix.h"
#endif
#ifdef USE_SRV_COM_CAN
#include "srv_com_can/srv_com_can_signal.h"
#endif

//=============================================================================
// Include device abstraction components
#ifdef USE_DD_JOYSTICK
#include "dd_joystick/dd_joystick.h"
#endif

//=============================================================================
// Include ECU abstraction components
#ifdef USE_ED_CAN_MCP
#include "ed_can_mcp/ed_can_mcp.h"
#endif
#ifdef USE_ED_ESC
#include "ed_esc/ed_esc.h"
#endif
#ifdef USE_DD_ENCODER
#include "dd_encoder/dd_encoder.h"
#endif
#ifdef USE_ED_BUZZER
#include "ed_buzzer/ed_buzzer.h"
#endif
#ifdef USE_ED_L298
#include "ed_l298/ed_l298.h"
#endif
#ifdef USE_DD_DC_MOTOR
#include "dd_dc_motor/dd_dc_motor.h"
#endif
#ifdef USE_CTRL_TRACTION
#include "ctrl_traction/ctrl_traction.h"
#endif
#ifdef USE_CTRL_STEERING
#include "ctrl_steering/ctrl_steering.h"
#endif

void setup()
{
#ifdef USE_SRV_UI_SERIAL
  srv_ui_serial_setup();
#endif

#ifdef USE_ED_CAN_MCP
  dd_can_setup();
#endif
#ifdef USE_SRV_COM_CAN
  dd_can_matrix_setup();
// dd_can_signal_setup();
#endif
#ifdef USE_DD_JOYSTICK
  dd_joystick_setup();
#endif
#ifdef USE_ED_BUZZER
  ed_buzzer_setup();
#endif
#ifdef USE_DD_ENCODER
  dd_encoder_setup();
#endif
#ifdef USE_ED_L298
  ed_l298_setup();
#endif

#ifdef USE_DD_DC_MOTOR
  dd_dc_motor_setup(); 
#endif

#ifdef USE_SRV_CONTROL
  srv_control_setup();
#endif

#ifdef USE_SRV_UI_LCD
  srv_ui_lcd_setup();
#endif
#ifdef USE_SRV_UI_BT
  srv_ui_bt_setup();
#endif

#ifdef USE_CTRL_TRACTION
  ctrl_traction_setup();
#endif
#ifdef USE_CTRL_STEERING
  ctrl_steering_setup();
#endif
}


#define SYS_TICK 1

#define CAN_SEND_REC (50 / SYS_TICK)
int send_rec_cnt = CAN_SEND_REC + 1;

#define CAN_RECV_REC (1 / SYS_TICK)
int recv_rec_cnt = CAN_RECV_REC + 2;

#define SRV_UI_SERIAL_OUT_REC (2000 / SYS_TICK)
int srv_serial_out_cnt = SRV_UI_SERIAL_OUT_REC + 3;

#define SRV_UI_SERIAL_IN_REC (1 / SYS_TICK)
int srv_serial_in_cnt = SRV_UI_SERIAL_IN_REC + 3;

#define SRV_UI_LC_REC (50 / SYS_TICK)
int lcd_rec_cnt = SRV_UI_LC_REC + 3;

#define SRV_UI_BT_REC (25 / SYS_TICK)
int bt_rec_cnt = SRV_UI_BT_REC + 3;

#define DD_JOYSTICK_REC (10 / SYS_TICK)
int dd_joystick_rec_cnt = DD_JOYSTICK_REC + 3;

#define DD_ENCODER_REC (1 / SYS_TICK)
int dd_encoder_rec_cnt = DD_ENCODER_REC + 4;

#define ED_BUZZER_REC (10 / SYS_TICK)
int ed_buzzer_rec_cnt = ED_BUZZER_REC + 4;

#define SRV_CONTROL_REC (500 / SYS_TICK)
int srv_control_rec_cnt = SRV_CONTROL_REC + 5;

#define ED_L298_REC (100 / SYS_TICK)
int ed_l298_rec_cnt = ED_L298_REC + 5;

#define CTRL_TRACTION_REC (1000 / SYS_TICK)
int ctrl_traction_rec_cnt = CTRL_TRACTION_REC + 5;

#define CTRL_STEERING_REC (100 / SYS_TICK)
int ctrl_steering_rec_cnt = CTRL_STEERING_REC + 5;


#define DD_DC_MOTOR_REC (100 / SYS_TICK)
int dd_dc_motor_rec_cnt = DD_DC_MOTOR_REC + 5;

void loop()
{
//=============================================================================
#ifdef USE_DD_JOYSTICK
  if (--dd_joystick_rec_cnt <= 0)
  {
    dd_joystick_loop();
    dd_joystick_rec_cnt = DD_JOYSTICK_REC;
  }
#endif

#ifdef USE_DD_ENCODER
  if (--dd_encoder_rec_cnt <= 0)
  {
    dd_encoder_loop();
    dd_encoder_rec_cnt = DD_ENCODER_REC;
  }
#endif

#ifdef USE_ED_BUZZER
  if (--ed_buzzer_rec_cnt <= 0)
  { // send data per 10ms
    ed_buzzer_loop();
    ed_buzzer_rec_cnt = ED_BUZZER_REC;
  }
#endif
  //=============================================================================
#ifdef USE_ED_L298
  if (--ed_l298_rec_cnt <= 0)
  { // send data per 10ms
    ed_l298_loop();
    ed_l298_rec_cnt = ED_L298_REC;
  }
#endif

#ifdef USE_CTRL_TRACTION
  if (--ctrl_traction_rec_cnt <= 0)
  { // send data per 10ms
    ctrl_traction_loop();
    ctrl_traction_rec_cnt = CTRL_TRACTION_REC;
  }
#endif

#ifdef USE_CTRL_STEERING
  if (--ctrl_steering_rec_cnt <= 0)
  { // send data per 10ms
    ctrl_steering_loop();
    ctrl_steering_rec_cnt = CTRL_STEERING_REC;
  }
#endif

#ifdef USE_DD_DC_MOTOR
  if (--dd_dc_motor_rec_cnt <= 0)
  { // send data per 10ms
    dd_dc_motor_loop();
    dd_dc_motor_rec_cnt = DD_DC_MOTOR_REC;
  }
#endif

//=============================================================================
#ifdef USE_SRV_CONTROL
  if (--srv_control_rec_cnt <= 0)
  {
    srv_control_loop();
    srv_control_rec_cnt = SRV_CONTROL_REC;
  }
#endif

#ifdef USE_SRV_COM_CAN
  if (--send_rec_cnt <= 0)
  { // send data per 100ms
    dd_can_send_loop();
    send_rec_cnt = CAN_SEND_REC;
  }
#endif

#ifdef USE_SRV_COM_CAN
  if (--recv_rec_cnt <= 0)
  {
    dd_can_recv_loop();
    dd_can_signal_loop();
    recv_rec_cnt = CAN_RECV_REC;
  }
#endif

#ifdef USE_SRV_UI_SERIAL
  if (--srv_serial_out_cnt <= 0)
  {
    srv_ui_serial_out_loop();
    srv_serial_out_cnt = SRV_UI_SERIAL_OUT_REC;
  }
#endif
#ifdef USE_SRV_UI_SERIAL
  // Task for reading commands from the serial terminal
  if (--srv_serial_in_cnt <= 0)
  {
    srv_ui_serial_in_loop();
    srv_serial_in_cnt = SRV_UI_SERIAL_IN_REC;
  }
#endif

#ifdef USE_SRV_UI_LCD
  if (--lcd_rec_cnt <= 0)
  { // print data per 100ms

    srv_ui_lcd_loop();
    lcd_rec_cnt = SRV_UI_LC_REC;
  }
#endif

#ifdef USE_SRV_UI_BT
  if (--bt_rec_cnt <= 0)
  { // print data per 100ms

    srv_ui_bt_loop();
    bt_rec_cnt = SRV_UI_BT_REC;
  }
#endif
  delay(SYS_TICK);
}

#include "Arduino.h"

#include "ed_can_mcp/ed_can_mcp.h"
#include "srv_com_can/srv_com_can_matrix.h"
#include "srv_com_can/srv_com_can_signal.h"

#include "dd_joystick/dd_joystick.h"
#include "ed_buzzer/ed_buzzer.h"
#include "srv_ui_lcd/srv_ui_lcd.h"
#include "srv_ui_bt/srv_ui_bt.h"

#include "srv_control/srv_control.h"

void setup()
{
  Serial.begin(9600);

  dd_can_setup();
  dd_can_matrix_setup();
  dd_joystick_setup();
  ed_buzzer_setup();

  srv_control_setup();
  srv_ui_lcd_setup();
  srv_ui_bt_setup();
}

#define SYS_TICK 1

#define CAN_SEND_REC (50 / SYS_TICK)
int send_rec_cnt = CAN_SEND_REC+1;

#define CAN_RECV_REC (1 / SYS_TICK)
int recv_rec_cnt = CAN_RECV_REC+2;

#define CAN_PRINT_REC (2000 / SYS_TICK)
int print_rec_cnt = CAN_PRINT_REC+3;

#define SRV_UI_LC_REC (50 / SYS_TICK)
int lcd_rec_cnt = SRV_UI_LC_REC+3;

#define SRV_UI_BT_REC (25 / SYS_TICK)
int bt_rec_cnt = SRV_UI_BT_REC+3;

#define DD_JOYSTICK_REC (10 / SYS_TICK)
int dd_joystick_rec_cnt = DD_JOYSTICK_REC+3;

#define ED_BUZZER_REC (10 / SYS_TICK)
int ed_buzzer_rec_cnt = ED_BUZZER_REC+4;

#define SRV_CONTROL_REC (500 / SYS_TICK)
int srv_control_rec_cnt = SRV_CONTROL_REC+5;


void loop()
{
  if (--dd_joystick_rec_cnt <= 0)
  {// send data per 10ms
    dd_joystick_loop();
    dd_joystick_rec_cnt = DD_JOYSTICK_REC;
  }  
  
  if (--ed_buzzer_rec_cnt <= 0)
  {// send data per 10ms
    ed_buzzer_loop();
    ed_buzzer_rec_cnt = ED_BUZZER_REC;
  }  

  if (--srv_control_rec_cnt <= 0)
  {
    srv_control_loop();
    srv_control_rec_cnt = SRV_CONTROL_REC;
  }  
  
  if (--send_rec_cnt <= 0)
  {// send data per 100ms
    dd_can_send_loop();
    send_rec_cnt = CAN_SEND_REC;
  }

  if (--recv_rec_cnt <= 0)
  {
    dd_can_recv_loop();
    dd_can_signal_loop();
    recv_rec_cnt = CAN_RECV_REC;
  }

  if (--print_rec_cnt <= 0)
  {// print data per 100ms
    dd_can_tx_matrix_print();
    dd_can_rx_matrix_print();
    // dd_joystick_report();
    // dd_can_tx_buff_print();
    srv_ui_bt_report();

    print_rec_cnt = CAN_PRINT_REC;
  }

  if (--lcd_rec_cnt <= 0)
  {// print data per 100ms

    srv_ui_lcd_loop();
    lcd_rec_cnt = SRV_UI_LC_REC;
  }

  if (--bt_rec_cnt <= 0)
  {// print data per 100ms

    srv_ui_bt_loop();
    bt_rec_cnt = SRV_UI_BT_REC;
  }

  delay(SYS_TICK); 
}

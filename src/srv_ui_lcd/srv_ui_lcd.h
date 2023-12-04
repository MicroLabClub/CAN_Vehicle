#ifndef SRV_UI_srv_ui_lcd_H_
#define SRV_UI_srv_ui_lcd_H_

#include "ecu_config.h"

void Srv_ui_lcd( void *pvParameters );

void srv_ui_lcd_setup();
void srv_ui_lcd_loop();

void srv_ui_lcd_SetScreeNr(int screenNr);

enum srv_ui_lcd_screen_t
{
  SRV_UI_LDC_SCREEN_DEFAULT,
  SRV_UI_LDC_SCREEN_JOYSTICK,
  SRV_UI_LDC_SCREEN_UI_BT,
  SRV_UI_LDC_SCREEN_2,
  SRV_UI_LDC_SCREEN_3,
  SRV_UI_LDC_SCREEN_4,
  SRV_UI_LDC_SCREEN_NR_OF

} ;


// va fi chemata din un task responsabil de LCD
void srv_ui_lcd_Joistick_B_Report();
void srv_ui_lcd_Joistick_X_Report();
void srv_ui_lcd_Joistick_Y_Report();
#endif
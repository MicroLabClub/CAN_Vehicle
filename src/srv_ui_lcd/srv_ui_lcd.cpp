
#include "Arduino.h"
#include "srv_ui_lcd.h"
#include "srv_com_can/srv_com_can_signal.h"
#include "srv_ui_bt/srv_ui_bt.h"

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4); // I2C address 0x27, 16 column and 2 rows


void srv_ui_lcd_Screen_DEFAULT(void);
void srv_ui_lcd_Screen_Joystick(void);
void srv_ui_lcd_Screen_UI_BT(void);


void srv_ui_lcd_setup()
{
  lcd.init(); // initialize the lcd
  lcd.backlight();
}

int srv_ui_lcd_screen_nr = SRV_UI_LDC_SCREEN_UI_BT;

void srv_ui_lcd_loop()
{

  switch (srv_ui_lcd_screen_nr)
  {
  case SRV_UI_LDC_SCREEN_DEFAULT:
    srv_ui_lcd_Screen_DEFAULT();
    break;
  case SRV_UI_LDC_SCREEN_JOYSTICK:
    srv_ui_lcd_Screen_Joystick();
    break;
  case SRV_UI_LDC_SCREEN_UI_BT:
    srv_ui_lcd_Screen_UI_BT();
    break;

  default:
    srv_ui_lcd_Screen_DEFAULT();

    break;
  }

}

void srv_ui_lcd_SetScreeNr(int screenNr)
{

  if (screenNr >= SRV_UI_LDC_SCREEN_NR_OF)
    screenNr = SRV_UI_LDC_SCREEN_DEFAULT;

  srv_ui_lcd_screen_nr = screenNr;
}

void srv_ui_lcd_Screen_DEFAULT(void)
{
  // Screen Default:
  // lcd.clear();         // clear display
  lcd.setCursor(0, 0); // move cursor to   (0, 0)
  lcd.print("Welcome to :");
  lcd.setCursor(0, 1); // move cursor to   (2, 1)
  lcd.print("Autonomous Vehicle");
  lcd.setCursor(0, 2); // move cursor to   (2, 1)
  lcd.print("Smart GolfCart");
}

void srv_ui_lcd_Screen_Joystick(void)
{
  // Screen 1:
  lcd.clear();         // clear display
  lcd.setCursor(0, 0); // move cursor to   (0, 0)
  lcd.print("B2 - Joistick setting");
  lcd.setCursor(0, 1); // move cursor to   (2, 1)
  srv_ui_lcd_Joistick_B_Report();
  lcd.setCursor(0, 2); // move cursor to   (0, 0)
  srv_ui_lcd_Joistick_X_Report();
  lcd.setCursor(0, 3); // move cursor to   (2, 1)
  srv_ui_lcd_Joistick_Y_Report();
}

char str_lcd[20];

void srv_ui_lcd_Screen_UI_BT(void)
{
  // Screen 1:
  // lcd.clear();         // clear display
  lcd.setCursor(0, 0); // move cursor to   (0, 0)
  int key_status = dd_can_signal_get_ui_bt(SRV_UI_BT_KEY_ID_FORWARD);
  sprintf(str_lcd, "F : %3d", key_status);
  lcd.print(str_lcd);
  lcd.setCursor(0, 1); // move cursor to   (0, 1)
  key_status = dd_can_signal_get_ui_bt(SRV_UI_BT_KEY_ID_BACKWARD);
  sprintf(str_lcd, "B : %3d", key_status);
  lcd.print(str_lcd);
  lcd.setCursor(0, 2); // move cursor to   (0, 2)
  key_status = dd_can_signal_get_ui_bt(SRV_UI_BT_KEY_ID_LEFT);
  sprintf(str_lcd, "L : %3d", key_status);
  lcd.print(str_lcd); 
  lcd.setCursor(0, 3); // move cursor to   (0, 3)
  key_status = dd_can_signal_get_ui_bt(SRV_UI_BT_KEY_ID_RIGHT);
  sprintf(str_lcd, "R : %3d", key_status);
  lcd.print(str_lcd);
  lcd.setCursor(10, 0); // move cursor to   (10, 0)
  key_status = dd_can_signal_get_ui_bt(SRV_UI_BT_KEY_ID_FORWARD_LEFT);  
  sprintf(str_lcd, "FL: %3d", key_status);
  lcd.print(str_lcd);
  lcd.setCursor(10, 1); // move cursor to   (10, 1)
  key_status = dd_can_signal_get_ui_bt(SRV_UI_BT_KEY_ID_FORWARD_RIGHT);
  sprintf(str_lcd, "FR: %3d", key_status);
  lcd.print(str_lcd);
  lcd.setCursor(10, 2); // move cursor to   (10, 2)
  key_status = dd_can_signal_get_ui_bt(SRV_UI_BT_KEY_ID_BACKWARD_LEFT);
  sprintf(str_lcd, "BL: %3d", key_status);
  lcd.print(str_lcd);
  lcd.setCursor(10, 3); // move cursor to   (10, 3)
  key_status = dd_can_signal_get_ui_bt(SRV_UI_BT_KEY_ID_BACKWARD_RIGHT);
  sprintf(str_lcd, "BR: %3d", key_status);
  lcd.print(str_lcd);
}

// va fi chemata din un task responsabil de Serial
void srv_ui_lcd_Joistick_B_Report()
{
  int button_state = dd_can_signal_get_bip();;

  if (button_state == LOW)
    lcd.print("Button is PRESSED");
  else if (button_state == HIGH)
    lcd.print("Button is RELEASED");
  else
    lcd.print("Undefined Button State");

}

void srv_ui_lcd_Joistick_X_Report()
{
  uint16_t x_coord = dd_can_signal_get_x();;
  lcd.print(" X: ");
  lcd.print(x_coord);
}


void srv_ui_lcd_Joistick_Y_Report()
{
  uint16_t y_coord = dd_can_signal_get_y();;
  lcd.print(" Y: ");
  lcd.print(y_coord);
}


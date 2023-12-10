#include "Arduino.h"
#include "srv_ui_lcd.h"
#include "srv_com_can/srv_com_can_signal.h"
#include "srv_ui_bt/srv_ui_bt.h"
#include "dd_joystick/dd_joystick.h"
#include "dd_encoder/dd_encoder.h"

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4); // I2C address 0x27, 16 column and 2 rows

enum srv_ui_lcd_screen_t
{
  SRV_UI_LDC_SCREEN_DEFAULT,
  SRV_UI_LDC_SCREEN_DUMMY_1,
  SRV_UI_LDC_SCREEN_JOYSTICK,
  SRV_UI_LDC_SCREEN_DUMMY_3,
  SRV_UI_LDC_SCREEN_UI_BT_KEY,
  SRV_UI_LDC_SCREEN_DUMMY_5,
  SRV_UI_LDC_SCREEN_UI_BT_POW_STEER,
  SRV_UI_LDC_SCREEN_DUMMY_7,
  SRV_UI_LDC_SCREEN_ENCODER,
  SRV_UI_LDC_SCREEN_DUMMY_9,
  SRV_UI_LDC_SCREEN_NR_OF

};

void srv_ui_lcd_SetScreeNr(int screenNr);

void srv_ui_lcd_Screen_DEFAULT(void);

// va fi chemata din un task responsabil de LCD
void srv_ui_lcd_Screen_Joystick(void);
void srv_ui_lcd_Joistick_B_Report();
void srv_ui_lcd_Joistick_X_Report();
void srv_ui_lcd_Joistick_Y_Report();

void srv_ui_lcd_Encoder_Report();
void srv_ui_lcd_Screen_Encoder(void);

void srv_ui_lcd_Screen_ui_bt_key(void);
void srv_ui_lcd_Screen_ui_bt_pow_steer(void);

void srv_ui_lcd_setup()
{
  lcd.init(); // initialize the lcd
  lcd.backlight();
}

uint8_t srv_ui_lcd_screen_nr = SRV_UI_LDC_SCREEN_ENCODER;

void srv_ui_lcd_loop()
{
  uint8_t new_screen_nr = dd_encoder_get_counter() % SRV_UI_LDC_SCREEN_NR_OF;
  if (new_screen_nr != srv_ui_lcd_screen_nr)
  {
    srv_ui_lcd_screen_nr = new_screen_nr;
    lcd.clear(); // clear display
  }

  switch (srv_ui_lcd_screen_nr)
  {
  case SRV_UI_LDC_SCREEN_DEFAULT:
    srv_ui_lcd_Screen_DEFAULT();
    break;
  case SRV_UI_LDC_SCREEN_JOYSTICK:
    srv_ui_lcd_Screen_Joystick();
    break;
  case SRV_UI_LDC_SCREEN_UI_BT_KEY:
    srv_ui_lcd_Screen_ui_bt_key();
    break;
  case SRV_UI_LDC_SCREEN_UI_BT_POW_STEER:
    srv_ui_lcd_Screen_ui_bt_pow_steer();
    break;
  case SRV_UI_LDC_SCREEN_ENCODER:
    srv_ui_lcd_Screen_Encoder();
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
  lcd.print(F("Welcome to :"));
  lcd.setCursor(0, 1); // move cursor to   (2, 1)
  lcd.print(F("Autonomous Vehicle"));
  lcd.setCursor(0, 2); // move cursor to   (2, 1)
  lcd.print(F("Smart GolfCart"));
}

void srv_ui_lcd_Screen_Joystick(void)
{
  // Screen 1:
  // lcd.clear();         // clear display
  lcd.setCursor(0, 0); // move cursor to   (0, 0)
  lcd.print(F("B2 - Joistick setting"));
  lcd.setCursor(0, 1); // move cursor to   (2, 1)
  srv_ui_lcd_Joistick_B_Report();
  lcd.setCursor(0, 2); // move cursor to   (0, 0)
  srv_ui_lcd_Joistick_X_Report();
  lcd.setCursor(0, 3); // move cursor to   (2, 1)
  srv_ui_lcd_Joistick_Y_Report();
}

void srv_ui_lcd_Screen_Encoder(void)
{
  // Screen 1:
  // lcd.clear();         // clear display
  lcd.setCursor(0, 0); // move cursor to   (0, 0)
  lcd.print(F(""));
  lcd.setCursor(0, 1); // move cursor to   (2, 1)
  srv_ui_lcd_Encoder_Report();
}

char str_lcd[20];

void srv_ui_lcd_Screen_ui_bt_key(void)
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

void srv_ui_lcd_Screen_ui_bt_pow_steer()
{
  // Screen 1:
  // lcd.clear();         // clear display
  lcd.setCursor(0, 0); // move cursor to   (0, 0)
  int power = dd_can_signal_get_bt_ui_power();
  sprintf(str_lcd, "    Power : %3d", power);
  lcd.print(str_lcd);
  lcd.setCursor(0, 2); // move cursor to   (0, 1)
  int steering = dd_can_signal_get_bt_ui_steering();
  sprintf(str_lcd, " Steering : %3d", steering);
  lcd.print(str_lcd);
}

// va fi chemata din un task responsabil de Serial
void srv_ui_lcd_Joistick_B_Report()
{
  int button_state = dd_can_signal_get_bip();

  if (button_state == LOW)
    lcd.print(F("Button is PRESSED"));
  else if (button_state == HIGH)
    lcd.print(F("Button is RELEASED"));
  else
    lcd.print(F("Undefined Button State"));
}

void srv_ui_lcd_Encoder_Report()
{
  int32_t encoder_cnt = dd_encoder_get_counter();
  lcd.print(F("Encoder: "));
  lcd.print(encoder_cnt);
}

void srv_ui_lcd_Joistick_X_Report()
{
  uint16_t x_coord = dd_can_signal_get_x();
  lcd.print(F(" X: "));
  lcd.print(x_coord);
}

void srv_ui_lcd_Joistick_Y_Report()
{
  uint16_t y_coord = dd_can_signal_get_y();
  lcd.print(F(" Y: "));
  lcd.print(y_coord);
}

#include "srv_ui_serial.h"
#include "ecu_config.h"
#include "Arduino.h"

// Control Components
// #include "ctrl_air_humidity/ctrl_air_humidity.h"
// #include "ctrl_lights/ctrl_lights.h"
// #include "ctrl_press_isol/ctrl_press_isol.h"
// #include "ctrl_soil_moisture/ctrl_soil_moisture.h"

#ifdef USE_CTRL_STEERING
#include "ctrl_steering/ctrl_steering.h"
#endif
#ifdef USE_CTRL_TRACTION
#include "ctrl_traction/ctrl_traction.h"
#endif

//=============================================================================
// Platform Services
#ifdef USE_SRV_COM_CAN
#include "srv_com_can/srv_com_can_matrix.h"
#endif
#ifdef USE_SRV_UI_BT
#include "srv_ui_bt/srv_ui_bt.h"
#endif

//=============================================================================
// Devise abstraction components

#ifdef USE_DD_DC_MOTOR
#include "dd_dc_motor/dd_dc_motor.h"
#endif
#ifdef USE_DD_JOYSTICK
#include "dd_joystick/dd_joystick.h"
#endif
#ifdef USE_DD_ENCODER
#include "dd_encoder/dd_encoder.h"
#endif

// ECU Abstraction components
#ifdef USE_ED_CAN_MCP
#include "ed_can_mcp/ed_can_mcp.h"
#endif
#ifdef USE_ED_L298
#include "ed_l298/ed_l298.h"
#endif

void srv_ui_serial_setup()
{
  Serial.begin(9600);
  Serial.println("Vehicle System started");
}

void srv_ui_serial_in_loop()
{
  // Serial.println("SCAN ");
  if (Serial.available())
  {
    char cmd = Serial.read();

    Serial.print("Vehicle: Recived command: ");
    Serial.println(cmd);

    switch (cmd)
    {

    case 'x': //  manual or automat control
#if defined USE_CTRL_TRACTION
      if (ctrl_traction_is_enabled())
      { // go to manual control
        Serial.println(" CTRL_TRACTION:  Change mode to MANUAL");
        ctrl_traction_disable();
      }
      else
      { // go to automat control
        Serial.println(" CTRL_TRACTION:  Change mode to AUTO");
        ctrl_traction_enable();
      }
#elif defined USE_DD_DC_MOTOR
      dd_dc_motor_set_power(DD_DC_MOTOR_ID_1, 0);
      Serial.println("DD_MOTOR: STOP Command");
#elif defined USE_ED_L298
      Serial.println("DD_L298: STOP Command");
      ed_l298_set(ED_L298_ID_1, LOW, LOW, 0);
#else
      Serial.println("CTRL_TRACTION: AUTO/MANUAL/STOP Command <no action>");
#endif
      break;

    case 'w': // UP
#if defined USE_CTRL_TRACTION
      if (ctrl_traction_is_enabled())
      {
        if (ctrl_traction_is_step_mode())
        {
          ctrl_traction_step_up(10);
          Serial.println("CTRL_TRACTION: Step UP");
        }
        else
        {
          ctrl_traction_power_up(10);
          Serial.println("CTRL_TRACTION: Manual Motor power UP");
        }
      }
#elif defined USE_DD_DC_MOTOR
      dd_dc_motor_set_power(DD_DC_MOTOR_ID_1, 255);
      Serial.println("DD_MOTOR: Motor forward");
#elif defined USE_ED_L298
      ed_l298_set(ED_L298_ID_1, LOW, HIGH, 255);
      Serial.println("DD_MOTOR: Motor Forward");
#else
      Serial.println("CTRL_TRACTION: OPEN/SP_Up Command <no action>");
#endif
      break;

    case 's': // Down
#if defined USE_CTRL_TRACTION
      if (ctrl_traction_is_enabled())
      {

        if (ctrl_traction_is_step_mode())
        {
          ctrl_traction_step_down(10);
          Serial.println("CTRL_TRACTION: Step DOWN");
        }
        else
        {
          ctrl_traction_power_down(10);
          Serial.println("CTRL_TRACTION: Manual Motor power DOWN");
        }
      }
#elif defined USE_DD_DC_MOTOR
      dd_dc_motor_set_power(DD_DC_MOTOR_ID_1, -255);
      Serial.println("DD_MOTOR: Motor backward");
#elif defined USE_ED_L298
      ed_l298_set(ED_L298_ID_1, HIGH, LOW, 255);
      Serial.println(" ED_L298: Motor Backward");
#else
      Serial.println("CTRL_TRACTION: CLOSE/SP_Dn Command <no action>");
#endif
      break;
    case 'z': //  manual or automat control
#if defined USE_CTRL_STEERING
      if (ctrl_steering_is_enabled())
      { // go to manual control
        Serial.println(" CTRL_STEERING: Change mode to MANUAL");
        ctrl_steering_disable();
      }
      else
      { // go to automat control
        Serial.println(" CTRL_STEERING: Change mode to AUTO");
        ctrl_steering_enable();
      }
#elif defined USE_DD_DC_MOTOR
      dd_dc_motor_set_power(DD_DC_MOTOR_ID_1, 0);
      Serial.println("DD_MOTOR: STOP Command");
#elif defined USE_ED_L298
      Serial.println("DD_L298: STOP Command");
      ed_l298_set(ED_L298_ID_1, LOW, LOW, 0);
#else
      Serial.println("CTRL_STEERING: AUTO/MANUAL/STOP Command <no action>");
#endif
      break;

    case 'a': // LEFT
#if defined USE_CTRL_STEERING
      if (ctrl_steering_is_enabled())
      {
        ctrl_steering_turn_left(10);
        Serial.println("CTRL_STEERING: Turn left");
      }
#elif defined USE_DD_DC_MOTOR
      dd_dc_motor_set_power(DD_DC_MOTOR_ID_1, 255);
      Serial.println("DD_MOTOR: Motor forward");
#elif defined USE_ED_L298
      ed_l298_set(ED_L298_ID_1, LOW, HIGH, 255);
      Serial.println("DD_MOTOR: Motor Forward");
#else
      Serial.println("CTRL_STEERING: UP Command <no action>");
#endif
      break;

    case 'd': // Right
#if defined USE_CTRL_STEERING
      if (ctrl_steering_is_enabled())
      {
        ctrl_steering_turn_right(10);
        Serial.println("CTRL_STEERING: Turn right");
      }
#elif defined USE_DD_DC_MOTOR
      dd_dc_motor_set_power(DD_DC_MOTOR_ID_1, -255);
      Serial.println("DD_MOTOR: Motor backward");
#elif defined USE_ED_L298
      ed_l298_set(ED_L298_ID_1, HIGH, LOW, 255);
      Serial.println(" ED_L298: Motor Backward");
#else
      Serial.println("CTRL_STEERING: DOWN Command <no action>");
#endif
      break;
    default:
      break;
    }
  }
}

void srv_ui_serial_out_loop()
{
  Serial.println(F("=============== Vehicle System Report =============== "));
#ifdef USE_SRV_COM_CAN
  dd_can_matrix_print();
#endif
#ifdef USE_CTRL_STEERING
  srv_ui_serial_ctrl_steering_report();
#endif
#ifdef USE_CTRL_TRACTION
  srv_ui_serial_ctrl_traction_report();
#endif
#ifdef USE_DD_DC_MOTOR
  srv_ui_serial_dd_motor_report();
#endif
#ifdef USE_ED_L298
  srv_ui_serial_ed_l298_report();
#endif
#ifdef USE_DD_SNS_ANGLE
  srv_ui_serial_dd_sns_angle_report();
#endif
#ifdef USE_ED_POTENTIOMETER
  srv_ui_serial_ed_pot_report();
#endif
#ifdef USE_DD_JOYSTICK
  dd_joystick_report();
#endif
#ifdef USE_DD_ENCODER
  dd_encoder_report();
#endif
#ifdef USE_SRV_UI_BT
  srv_ui_bt_report();
#endif
  Serial.println();
}

void srv_ui_serial_ed_l298_report()
{
#ifdef USE_ED_L298
  Serial.print("ED_L298: ");
  for (size_t driver_id = 0; driver_id < ED_L298_NR_OF; driver_id++)
  {
    ed_l298_t *ed_l298_ref = ed_l298_get_ref(driver_id);

    Serial.print(F("[Driver "));
    Serial.print(driver_id);
    Serial.print(F("] - "));
    Serial.print(ed_l298_ref->in_1);
    Serial.print(F(":"));
    Serial.print(ed_l298_ref->in_2);
    Serial.print(F(":"));
    Serial.print(ed_l298_ref->en);
    Serial.print(F("   "));
  }
  Serial.println();
#endif
}

void srv_ui_serial_dd_motor_report()
{
#ifdef USE_DD_DC_MOTOR
  Serial.print("DD_DC_MOTOR: ");

  for (size_t motor_id = 0; motor_id < DD_DC_MOTOR_NR_OF; motor_id++)
  {
    int16_t motor_pow = dd_dc_motor_get_power(motor_id);

    Serial.print(F("[Motor "));
    Serial.print(motor_id);
    Serial.print(F("] - "));
    Serial.print(motor_pow);

    Serial.print(F("   "));
  }
  Serial.println();
#endif
}

void srv_ui_serial_ed_pot_report()
{
#ifdef USE_ED_POTENTIOMETER
  if (ed_dht_GetTemperatureError() == 0)
  {
    float temp = ed_dht_GetTemperature();
    Serial.print(F("ED_DHT Temperature: "));
    Serial.print(temp);
    Serial.println(F("°C"));
  }
  else
  {
    Serial.println(F("ED_DHT Error reading temperature!"));
  }
#endif
}

void srv_ui_serial_dd_encoder_report()
{
#ifdef USE_DD_ENCODER
  float enc_cnt = dd_encoder_get_counter();
  Serial.print(F("DD_ENCODER Counter: "));
  Serial.print(enc_cnt);
  Serial.println();
#endif
}

//----------------------------------------------------------
// Angle sensor report
//----------------------------------------------------------
void srv_ui_serial_dd_sns_angle_report()
{
#ifdef USE_SRV_SNS_AIR_TEMP
  float temp = srv_sns_air_GetTemperature();
  Serial.print(F("SRV_SNS_AIR_TEMP: Temperature: "));
  Serial.print(temp);
  Serial.println(F("°C"));
#endif
}

void srv_ui_serial_ctrl_traction_report()
{
#ifdef USE_CTRL_TRACTION

  Serial.print(F("CTRL_TRACTION:"));

  if (ctrl_traction_is_enabled())
  {
    Serial.print(F(" ENABLE "));
  }
  else
  {
    Serial.print(F(" DISABLE "));
  }

  Serial.print(F("Ctrl -"));

  if (ctrl_traction_get_target_mode() == CTRL_TRACTION_TARGET_MODE_CAN)
  {
    Serial.print(F(" CAN "));
  }
  else if (ctrl_traction_get_target_mode() == CTRL_TRACTION_TARGET_MODE_BT)
  {
    Serial.print(F(" BT "));
  }
  else if (ctrl_traction_get_target_mode() == CTRL_TRACTION_TARGET_MODE_MANUAL)
  {
    Serial.print(F(" MANUAL "));
  }
  else
  {
    Serial.print(F(" UNKNOWN  "));
  }

  Serial.print(F("FB - "));

  if (ctrl_traction_get_fb_mode() == CTRL_TRACTION_FB_MODE_POTENTIOMETER)
  {
    Serial.print(F("POTENTIOMETER  "));
  }
  else if (ctrl_traction_get_fb_mode() == CTRL_TRACTION_FB_MODE_TIMER)
  {
    Serial.print(F("TIMER "));
  }
  else if (ctrl_traction_get_fb_mode() == CTRL_TRACTION_FB_MODE_ENCODER)
  {
    Serial.print(F("ENCODER  "));
  }
  else
  {
    Serial.print(F(" UNKNOWN  "));
  }

  int16_t ctrl_power = ctrl_traction_get_power();
  Serial.print(F("Power = "));
  Serial.print(ctrl_power);

  int16_t current_step = ctrl_traction_get_current_step();
  Serial.print(F(": CS = "));
  Serial.print(current_step);

  int16_t target_step = ctrl_traction_get_target_step();
  Serial.print(F(" TS = "));
  Serial.println(target_step);

#endif
}

void srv_ui_serial_ctrl_steering_report()
{
#ifdef USE_CTRL_STEERING
  Serial.print(F("CTRL_STEERING:"));

  if (ctrl_steering_is_enabled())
  {
    Serial.print(F(" ENABLE "));
  }
  else
  {
    Serial.print(F(" DISABLE "));
  }

  Serial.print(F("Ctrl -"));

  if (ctrl_steering_get_target_mode() == CTRL_STEERING_TARGET_MODE_CAN)
  {
    Serial.print(F(" CAN "));
  }
  else if (ctrl_steering_get_target_mode() == CTRL_STEERING_TARGET_MODE_BT)
  {
    Serial.print(F(" BT "));
  }
  else if (ctrl_steering_get_target_mode() == CTRL_STEERING_TARGET_MODE_MANUAL)
  {
    Serial.print(F(" MANUAL "));
  }
  else
  {
    Serial.print(F(" UNKNOWN  "));
  }

  Serial.print(F("FB - "));

  if (ctrl_steering_get_fb_mode() == CTRL_STEERING_FB_MODE_POTENTIOMETER)
  {
    Serial.print(F("POTENTIOMETER  "));
  }
  else if (ctrl_steering_get_fb_mode() == CTRL_STEERING_FB_MODE_TIMER)
  {
    Serial.print(F("TIMER "));
  }
  else if (ctrl_steering_get_fb_mode() == CTRL_STEERING_FB_MODE_ENCODER)
  {
    Serial.print(F("ENCODER  "));
  }
  else
  {
    Serial.print(F(" UNKNOWN  "));
  }

  int16_t ctrl_power = ctrl_steering_get_power();
  Serial.print(F("Power = "));
  Serial.print(ctrl_power);

  int16_t current_angle = ctrl_steering_get_current_angle();
  Serial.print(F(": CA = "));
  Serial.print(current_angle);

  float target_angle = ctrl_steering_get_target_angle();
  Serial.print(F(" TA = "));
  Serial.println(target_angle);

#endif
}

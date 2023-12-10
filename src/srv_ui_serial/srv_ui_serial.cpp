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

//=============================================================================
// Devise abstraction components

#ifdef USE_DD_DC_MOTOR
#include "dd_dc_motor/dd_dc_motor.h"
#endif
#ifdef USE_DD_JOYSTICK
#include "dd_joystick/dd_joystick.h"
#endif
#ifdef USE_ED_ED_ENCODER
#include "ed_encoder/ed_encoder.h"
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
  Serial.begin(115200);
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
      if (ctrl_traction_is_enable())
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
      dd_dc_motor_set_power(DD_DC_MOTOR_ID_1,0);
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
      if (ctrl_traction_is_enable()==0)
      {
        ctrl_traction_power_up(10);
        Serial.println("CTRL_TRACTION: Manual Motor power UP");
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
      if (ctrl_traction_is_enable( )==0)
      {
        ctrl_traction_power_down(10);
        Serial.println("CTRL_TRACTION: Manual Motor power DOWN");
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

void srv_ui_serial_ctrl_steering_report()
{
#ifdef USE_CTRL_STEERING

  if (ctrl_steering_is_enabled())
  {
    Serial.println(F("CTRL_STEERING: Mode AUTO "));
  }
  else
  {
    Serial.println(F("CTRL_STEERING: Mode MANUAL"));
  }

  float temp_setpoint = ctrl_steering_get_setpoint();
  Serial.print(F("CTRL_STEERING: SP: "));
  Serial.print(temp_setpoint);
  Serial.print(F("°C "));

  Serial.print(F("HIST[OP: "));
  Serial.print(temp_setpoint + TEMP_VENT_HISTERESIS);
  Serial.print(F("°C  "));

  Serial.print(F("CL: "));
  Serial.print(temp_setpoint - TEMP_VENT_HISTERESIS);
  Serial.print(F("°C] "));

  float temp_current = ctrl_steering_get_current_temp();
  Serial.print(F("CTRL_STEERING: Cur: "));
  Serial.print(temp_current);
  Serial.println(F("°C"));

#endif
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
  // if (ctrl_traction_is_enabled())
  // {
  //   Serial.println(F("CTRL_TRACTION: Enabled "));
  // }
  // else
  // {
  //   Serial.println(F("CTRL_TRACTION: Disabled"));
  // }

  int16_t tract_pow = ctrl_traction_get_power();
  Serial.print(F("CTRL_TRACTION: Pow = "));
  Serial.println(tract_pow);

#endif
}


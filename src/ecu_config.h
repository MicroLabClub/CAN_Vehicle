#ifndef ECU_CONFIG_H_
#define ECU_CONFIG_H_

#define ECU_TST 0
#define ECU_UI_LCD 1
#define ECU_UI_BLUETOOTH 2
#define ECU_STEERING 3
#define ECU_TRACTION 4
#define ECU_OMNIWHEEL 5






// #define ECU_CONFIG ECU_UI_BLUETOOTH
// #define ECU_CONFIG ECU_UI_LCD
// #define ECU_CONFIG ECU_TRACTION
// #define ECU_CONFIG ECU_OMNIWHEEL
#define ECU_CONFIG ECU_STEERING
// #define ECU_CONFIG ECU_TST



#define CAN_ID_BUZZER   0x111
#define CAN_ID_JOYSTICK 0x222
#define CAN_ID_UI_BT    0x055
#define CAN_ID_UI_BT_CHASSIS    0x077
// to implement a claim mechanism on can
// when many ecu reports the same message


#if ECU_CONFIG == ECU_TST 

#define USE_SRV_UI_SERIAL
#define USE_DC_MOTOR
#define USE_DD_JOYSTICK
#define USE_ED_BUZZER
#define USE_ED_CAN_MCP
#define USE_ED_ESC
#define USE_DD_ENCODER
#define USE_ED_L298
#define USE_SRV_COM_CAN
#define USE_SRV_CONTROL
#define USE_SRV_UI_BT
#define USE_SRV_UI_LCD
#define USE_CTRL_TRACTION


#define TX_CAN_ID_NR_OF 4
#define TX_CAN_ID_LIST {CAN_ID_BUZZER, CAN_ID_JOYSTICK, CAN_ID_UI_BT, CAN_ID_UI_BT_CHASSIS}
#define RX_CAN_ID_NR_OF 4
#define RX_CAN_ID_LIST {CAN_ID_JOYSTICK, CAN_ID_BUZZER, CAN_ID_UI_BT, CAN_ID_UI_BT_CHASSIS}

#elif ECU_CONFIG == ECU_UI_LCD

#include "ecu_config_ui_lcd.h"

#elif ECU_CONFIG == ECU_UI_BLUETOOTH

#include "ecu_config_ui_bt.h"

#elif ECU_CONFIG == ECU_STEERING        

#include "ecu_config_steering.h"

#elif ECU_CONFIG == ECU_TRACTION        

#include "ecu_config_traction.h"

#elif ECU_CONFIG == ECU_OMNIWHEEL        

#include "ecu_config_omniwheel.h"

#endif

// BUZZER ECU CONFIG
#define ED_BUZZER_PIN A6

// CAN MCP ECU CONFIG
#define CAN0_INT 2 // Set INT to pin 2
#define CAN0_CS 10 // Set CS to pin 2

// JOYSTICK ECU CONFIG
// Joystick PinMap
#define DD_JOYSTICK_X A0
#define DD_JOYSTICK_Y A1
#define DD_JOYSTICK_B A2




#endif

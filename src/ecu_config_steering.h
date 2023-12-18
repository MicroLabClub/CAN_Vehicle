#ifndef ECU_CONFIG_STEERING_H_
#define ECU_CONFIG_STEERING_H_

// #define USE_CTRL_TRACTION
#define USE_CTRL_STEERING

#define USE_SRV_UI_SERIAL
#define USE_SRV_COM_CAN
// #define USE_SRV_UI_LCD
// #define USE_SRV_UI_BT
// #define USE_SRV_CONTROL

#define USE_DD_DC_MOTOR
// #define USE_DD_ENCODER
// #define USE_DD_JOYSTICK

// #define USE_ED_BUZZER
#define USE_ED_CAN_MCP
// #define USE_ED_ESC
#define USE_ED_L298



#define CTRL_STEERING_TARGET_MODE CTRL_STEERING_TARGET_MODE_CAN


#ifndef ED_L298_IN_1_PIN_LIST
#define ED_L298_IN_1_PIN_LIST { 7}
#endif
#ifndef ED_L298_IN_2_PIN_LIST
#define ED_L298_IN_2_PIN_LIST { 8}
#endif
#ifndef ED_L298_EN_PIN_LIST
#define ED_L298_EN_PIN_LIST { 9}
#endif


#define DD_DC_MOTOR_MAX_POWER 70
#define DD_DC_MOTOR_MIN_POWER -70


#define TX_CAN_ID_NR_OF 0
#define TX_CAN_ID_LIST {}
#define RX_CAN_ID_NR_OF 1
#define RX_CAN_ID_LIST {CAN_ID_UI_BT_CHASSIS}

#endif

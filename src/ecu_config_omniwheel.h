#ifndef ECU_CONFIG_OMNIWHEEL_
#define ECU_CONFIG_OMNIWHEEL_

#define ECU_OMNI_WHEEL_FL 3
#define ECU_OMNI_WHEEL_FR 4
#define ECU_OMNI_WHEEL_BL 5
#define ECU_OMNI_WHEEL_BR 6
#define ECU_OMNI_WHEEL_ALL 7

#define USE_SRV_UI_SERIAL
#define USE_DD_DC_MOTOR
// #define USE_DD_JOYSTICK
// #define USE_ED_BUZZER
#define USE_ED_CAN_MCP
// #define USE_ED_ESC
// #define USE_DD_ENCODER
#define USE_ED_L298
#define USE_SRV_COM_CAN
// #define USE_SRV_CONTROL
// #define USE_SRV_UI_BT
// #define USE_SRV_UI_LCD
#define USE_CTRL_TRACTION
#define USE_CTRL_STEERING

#define CAN0_INT 2 // Set INT to pin 2
#define CAN0_CS 10 // Set CS to pin 2

#define TX_CAN_ID_NR_OF 0
#define TX_CAN_ID_LIST {}
#define RX_CAN_ID_NR_OF 3
#define RX_CAN_ID_LIST {CAN_ID_UI_BT_CHASSIS, CAN_ID_UI_BT, CAN_ID_JOYSTICK}



#endif /* ECU_CONFIG_OMNIWHEEL_ */
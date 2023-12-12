#ifndef ECU_CONFIG_TRACTION_H_
#define ECU_CONFIG_TRACTION_H_


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

#define TX_CAN_ID_NR_OF 0
#define TX_CAN_ID_LIST {}
#define RX_CAN_ID_NR_OF 1
#define RX_CAN_ID_LIST {CAN_ID_UI_BT_CHASSIS}


#endif

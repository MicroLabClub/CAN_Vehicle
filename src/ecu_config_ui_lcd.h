#ifndef ECU_CONFIG_UI_LCD_H_
#define ECU_CONFIG_UI_LCD_H_


#define USE_SRV_UI_SERIAL
// #define USE_DC_MOTOR
// #define USE_DD_JOYSTICK
#define USE_ED_BUZZER
#define USE_ED_CAN_MCP
// #define USE_ED_ESC
#define USE_DD_ENCODER
// #define USE_ED_L298
#define USE_SRV_COM_CAN
// #define USE_SRV_CONTROL
// #define USE_SRV_UI_BT
#define USE_SRV_UI_LCD

// CAN MCP ECU CONFIG
#define CAN0_INT 2 // Set INT to pin 2
#define CAN0_CS 10 // Set CS to pin 2

#define TX_CAN_ID_NR_OF 0
#define TX_CAN_ID_LIST {}
#define RX_CAN_ID_NR_OF 4
#define RX_CAN_ID_LIST {CAN_ID_JOYSTICK, CAN_ID_BUZZER, CAN_ID_UI_BT, CAN_ID_UI_BT_CHASSIS}


#endif

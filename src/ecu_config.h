#ifndef ECU_CONFIG_H_
#define ECU_CONFIG_H_

#define ECU_TST 0
#define ECU_LCD 1
#define ECU_JOISTICK 2


#define ECU_OMNI_WHEEL_FL 3
#define ECU_OMNI_WHEEL_FR 4
#define ECU_OMNI_WHEEL_BL 5
#define ECU_OMNI_WHEEL_BR 6
#define ECU_OMNI_WHEEL_ALL 7




#define ECU_CONFIG ECU_TST

#define CAN_ID_BUZZER   0x111
#define CAN_ID_JOYSTICK 0x222
#define CAN_ID_UI_BT    0x055
// to implement a claim mechanism on can
// when many ecu reports the same message


#if ECU_CONFIG == ECU_TST 

#define TX_CAN_ID_NR_OF 3
#define TX_CAN_ID_LIST {CAN_ID_BUZZER, CAN_ID_JOYSTICK, CAN_ID_UI_BT}
#define RX_CAN_ID_NR_OF 3
#define RX_CAN_ID_LIST {CAN_ID_JOYSTICK, CAN_ID_BUZZER, CAN_ID_UI_BT}

#elif ECU_CONFIG == ECU_LCD

#define TX_CAN_ID_NR_OF 1
#define TX_CAN_ID_LIST {CAN_ID_BUZZER}
#define RX_CAN_ID_NR_OF 1
#define RX_CAN_ID_LIST {CAN_ID_JOYSTICK}

#elif ECU_CONFIG == ECU_JOISTICK

#define TX_CAN_ID_NR_OF 1
#define TX_CAN_ID_LIST {CAN_ID_JOYSTICK}
#define RX_CAN_ID_NR_OF 1
#define RX_CAN_ID_LIST {CAN_ID_BUZZER}

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

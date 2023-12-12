#include "ed_can_mcp/ed_can_mcp.h"
#include "srv_com_can_signal.h"
#include "srv_com_can_matrix.h"
#include "dd_joystick/dd_joystick.h"
#include "srv_ui_bt/srv_ui_bt.h"
#include "stdint.h"
#include "Arduino.h"

void dd_can_signal_loop()
{
    #ifdef USE_DD_JOYSTICK
    dd_can_signal_set_joistick();
    #endif
    #ifdef USE_SRV_UI_BT
    dd_can_signal_set_ui_bt();
    dd_can_signal_set_bt_ui_chassis();
    #endif
}

#ifdef CAN_ID_JOYSTICK

void dd_can_signal_set_joistick()
{
    uint16_t x = dd_joystick_get_x();
    uint16_t y = dd_joystick_get_y();
    uint8_t b = dd_joystick_get_b();

    can_message_t *tx_buff = dd_can_matrix_get_msg_ref(CAN_ID_JOYSTICK);
    // Serial.print("ID:");
    // Serial.println(tx_buff->id);
    if (tx_buff != NULL) {
        tx_buff->tx_msg[0] = (x >> 8) & 0xFF; // HIGH Byte X
        tx_buff->tx_msg[1] = x & 0xFF;        // Low Byte X
        tx_buff->tx_msg[2] = (y >> 8) & 0xFF; // High Byte Y
        tx_buff->tx_msg[3] = y & 0xFF;        // Low Byte Y
        tx_buff->tx_msg[4] = b; // Button state
    } else {
        Serial.print(F("JOISTICK: tx_buff is NULL , tx_ID:"));
        Serial.println(CAN_ID_JOYSTICK,HEX);
    }
}

#endif

#ifdef CAN_ID_JOYSTICK
uint8_t dd_can_signal_get_bip()
{
    can_message_t *msg_buff = dd_can_matrix_get_msg_ref(CAN_ID_JOYSTICK);
    uint8_t bip_sig = 0;
    if (msg_buff != NULL) {
        bip_sig = msg_buff->rx_msg[4];
    } else {
        Serial.println(F("BIP: msg_buff is NULL"));
    }
    return bip_sig;
}

uint16_t dd_can_signal_get_x()
{
    can_message_t *msg_buff = dd_can_matrix_get_msg_ref(CAN_ID_JOYSTICK);
    uint16_t high_byte = msg_buff->rx_msg[0];
    uint16_t low_byte = msg_buff->rx_msg[1];
    uint16_t x_coord = low_byte;
    x_coord += high_byte << 8;
    return x_coord;
}

uint16_t dd_can_signal_get_y()
{
    can_message_t *msg_buff = dd_can_matrix_get_msg_ref(CAN_ID_JOYSTICK);
    uint16_t high_byte = msg_buff->rx_msg[2];
    uint16_t low_byte = msg_buff->rx_msg[3];
    uint16_t y_coord = low_byte;
    y_coord += high_byte << 8;
    return y_coord;
}
#endif

#ifdef CAN_ID_UI_BT
uint8_t dd_can_signal_get_ui_bt(uint8_t key_id)
{
    can_message_t *msg_buff = dd_can_matrix_get_msg_ref(CAN_ID_UI_BT);
    uint8_t key_sig = msg_buff->rx_msg[key_id];
    return key_sig;
}

void dd_can_signal_set_ui_bt()
{
    can_message_t *tx_buff = dd_can_matrix_get_msg_ref(CAN_ID_UI_BT);
    for (uint8_t key_id = 0; key_id < SRV_UI_BT_KEY_ID_NR_OF; key_id++) {
        tx_buff->tx_msg[key_id] = (uint8_t)(srv_ui_bt_get_key_status(key_id));
    }
}

void dd_can_signal_set_bt_ui_chassis()
{
    can_message_t *tx_buff = dd_can_matrix_get_msg_ref(CAN_ID_UI_BT_CHASSIS);
    int16_t power = srv_ui_bt_get_power();
    uint16_t steering = srv_ui_bt_get_steering();
    tx_buff->tx_msg[0] = (power >> 8) & 0xFF; // HIGH Byte X
    tx_buff->tx_msg[1] = power & 0xFF;        // Low Byte X
    tx_buff->tx_msg[2] = (steering >> 8) & 0xFF; // High Byte Y
    tx_buff->tx_msg[3] = steering & 0xFF;        // Low Byte Y
}

uint16_t dd_can_signal_get_bt_ui_power()
{
    can_message_t *msg_buff = dd_can_matrix_get_msg_ref(CAN_ID_UI_BT_CHASSIS);
    uint16_t high_byte = msg_buff->rx_msg[0];
    uint16_t low_byte = msg_buff->rx_msg[1];
    uint16_t power = low_byte;
    power += high_byte << 8;
    return power;
}

uint16_t dd_can_signal_get_bt_ui_steering()
{
    can_message_t *msg_buff = dd_can_matrix_get_msg_ref(CAN_ID_UI_BT_CHASSIS);
    uint16_t high_byte = msg_buff->rx_msg[2];
    uint16_t low_byte = msg_buff->rx_msg[3];
    uint16_t steering = low_byte;
    steering += high_byte << 8;
    return steering;
}

#endif

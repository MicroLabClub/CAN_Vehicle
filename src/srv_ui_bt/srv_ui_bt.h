#ifndef SRV_UI_BT_
#define SRV_UI_BT_

#include "stdint.h"
#include "ecu_config.h"

enum srv_ui_bt_key_id_t
{
    SRV_UI_BT_KEY_ID_FORWARD,
    SRV_UI_BT_KEY_ID_BACKWARD,
    SRV_UI_BT_KEY_ID_LEFT,
    SRV_UI_BT_KEY_ID_RIGHT,
    SRV_UI_BT_KEY_ID_FORWARD_LEFT,
    SRV_UI_BT_KEY_ID_FORWARD_RIGHT,
    SRV_UI_BT_KEY_ID_BACKWARD_LEFT,
    SRV_UI_BT_KEY_ID_BACKWARD_RIGHT,
    SRV_UI_BT_KEY_ID_NR_OF
};

#define SRV_UI_BT_ROLLBACK_ENABLED 1
#define SRV_UI_BT_ROLLBACK_DISABLED 0

#ifndef SRV_UI_BT_ROLLBACK_DEFAULT
#define SRV_UI_BT_ROLLBACK_DEFAULT SRV_UI_BT_ROLLBACK_ENABLED
#endif



int16_t srv_ui_bt_get_power();
int16_t srv_ui_bt_get_steering();

float srv_ui_bt_get_key_status(uint8_t key_id);
void srv_ui_bt_set_key_status_max(uint8_t key_id, float max);
void srv_ui_bt_set_key_inc(uint8_t key_id, float inc);
void srv_ui_bt_set_key_dec(uint8_t key_id, float dec);
int16_t srv_ui_bt_get_key_id(char key);
void srv_ui_bt_set_key_status(uint8_t key_id, float status);
void srv_ui_bt_report();
int16_t srv_ui_bt_get_power();
int16_t srv_ui_bt_get_steering();

void srv_ui_bt_setup();
void srv_ui_bt_loop();



#endif
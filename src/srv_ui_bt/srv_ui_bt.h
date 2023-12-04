#ifndef SRV_UI_BT_
#define SRV_UI_BT_

#include "stdint.h"

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

float srv_ui_bt_get_key_status(srv_ui_bt_key_id_t key_id);
void srv_ui_bt_set_key_status_max(srv_ui_bt_key_id_t key_id, float max);
void srv_ui_bt_set_key_inc(srv_ui_bt_key_id_t key_id, float inc);
void srv_ui_bt_set_key_dec(srv_ui_bt_key_id_t key_id, float dec);
int16_t srv_ui_bt_get_key_id(char key);
void srv_ui_bt_set_key_status(srv_ui_bt_key_id_t key_id, float status);
void srv_ui_bt_report();


void srv_ui_bt_setup();
void srv_ui_bt_loop();



#endif
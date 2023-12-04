#include "srv_ui_bt.h"
#include "Arduino.h"
#include <SoftwareSerial.h>

SoftwareSerial srv_ui_bt_Serial(2, 3); // RX, TX

float srv_bt_key_status[SRV_UI_BT_KEY_ID_NR_OF] = {0, 0, 0, 0, 0, 0, 0, 0};
float srv_bt_key_status_max[SRV_UI_BT_KEY_ID_NR_OF] = {100, 100, 100, 100, 100, 100, 100, 100};
float srv_bt_key_inc[SRV_UI_BT_KEY_ID_NR_OF] = {1, 1, 1, 1, 1, 1, 1, 1};
float srv_bt_key_dec[SRV_UI_BT_KEY_ID_NR_OF] = {1, 1, 1, 1, 1, 1, 1, 1};
char srv_bt_key_char[SRV_UI_BT_KEY_ID_NR_OF] = {'F', 'B', 'L', 'R', 'G', 'I', 'H', 'J'};

void srv_ui_bt_setup()
{
    srv_ui_bt_Serial.begin(9600);
    Serial.println("SRV_UI_BT: Started");
}

void srv_ui_bt_loop()
{

    if (srv_ui_bt_Serial.available())
    {
        char cmd = srv_ui_bt_Serial.read();

        // Serial.print("SRV_UI_BT: Received command: ");
        // Serial.println(cmd);

        switch (cmd)
        {
        case 'S':
            /* Heart beat */
            break;

        default:
            size_t key_id = srv_ui_bt_get_key_id(cmd);
            if (key_id < SRV_UI_BT_KEY_ID_NR_OF && key_id >= 0)
            {
                // increment the key status
                srv_bt_key_status[key_id] += srv_bt_key_inc[key_id];

                // compensation for the dec at the end of the loop
                srv_bt_key_status[key_id] += srv_bt_key_dec[key_id];

                if (srv_bt_key_status[key_id] > srv_bt_key_status_max[key_id])
                {
                    srv_bt_key_status[key_id] = srv_bt_key_status_max[key_id];
                }
            }
            else
            {
                Serial.print("SRV_UI_BT: Unknown command: ");
                Serial.println(cmd);
            }
            break;
        }
    }
    // decrement the key status for all keys at the end of the loop
    for (size_t key_id = 0; key_id < SRV_UI_BT_KEY_ID_NR_OF; key_id++)
    {
        if (srv_bt_key_status[key_id] > 0)
        {
            srv_bt_key_status[key_id] -= srv_bt_key_dec[key_id];
        }
        else
        {
            srv_bt_key_status[key_id] = 0;
        }
    }
}

float srv_ui_bt_get_key_status(srv_ui_bt_key_id_t key_id)
{
    return srv_bt_key_status[key_id];
}

void srv_ui_bt_set_key_status_max(srv_ui_bt_key_id_t key_id, float max)
{
    srv_bt_key_status_max[key_id] = max;
}

void srv_ui_bt_set_key_inc(srv_ui_bt_key_id_t key_id, float inc)
{
    srv_bt_key_inc[key_id] = inc;
}

void srv_ui_bt_set_key_dec(srv_ui_bt_key_id_t key_id, float dec)
{
    srv_bt_key_dec[key_id] = dec;
}

int16_t srv_ui_bt_get_key_id(char key)
{
    for (size_t key_id = 0; key_id < SRV_UI_BT_KEY_ID_NR_OF; key_id++)
    {
        if (srv_bt_key_char[key_id] == key)
        {
            return key_id;
        }
    }
    return -1;
}

void srv_ui_bt_report()
{
    Serial.print("SRV_UI_BT Rep key: ");
    for (size_t key_id = 0; key_id < SRV_UI_BT_KEY_ID_NR_OF; key_id++)
    {
        Serial.print(srv_bt_key_char[key_id]);
        Serial.print(":");
        Serial.print(srv_bt_key_status[key_id]);
        Serial.print(" ");
    }
    Serial.println();
}
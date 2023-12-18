#include "srv_ui_bt.h"
#include "Arduino.h"
#include <SoftwareSerial.h>

SoftwareSerial srv_ui_bt_Serial(2, 3); // RX, TX

float srv_bt_ui_key_status[SRV_UI_BT_KEY_ID_NR_OF] = {0, 0, 0, 0, 0, 0, 0, 0};
float srv_bt_ui_key_status_max[SRV_UI_BT_KEY_ID_NR_OF] = {100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000};
float srv_bt_ui_key_status_min[SRV_UI_BT_KEY_ID_NR_OF] = {0, 0, 0, 0, 0, 0, 0, 0};
float srv_bt_ui_key_inc[SRV_UI_BT_KEY_ID_NR_OF] = {1, 1, 1, 1, 1, 1, 1, 1};
float srv_bt_ui_key_dec[SRV_UI_BT_KEY_ID_NR_OF] = { 1, 1, 1, 1, 1, 1, 1, 1};
char srv_bt_ui_key_char[SRV_UI_BT_KEY_ID_NR_OF] = {'F', 'B', 'L', 'R', 'G', 'I', 'H', 'J'};

int16_t srv_ui_bt_power = 0;
int16_t srv_ui_bt_steering = 0;

int8_t srv_ui_bt_roll_back_mode = SRV_UI_BT_ROLLBACK_DEFAULT;

int16_t srv_ui_bt_get_power()
{
    return srv_ui_bt_power;
}

int16_t srv_ui_bt_get_steering()
{
    return srv_ui_bt_steering;
}

void srv_ui_bt_setup()
{
    srv_ui_bt_Serial.begin(9600);
    Serial.println(F("SRV_UI_BT: Started"));
}

void srv_ui_bt_loop()
{

    if (srv_ui_bt_Serial.available())
    {
        char cmd = srv_ui_bt_Serial.read();

        // Serial.print(F("SRV_UI_BT: Received command: "));
        // Serial.println(cmd);

        switch (cmd)
        {
        case 'S':
            /* Heart beat */
            break;
        case 'U':
        case 'u': 
        case 'W':
        case 'w':
            for (uint8_t key_id = 0; key_id < SRV_UI_BT_KEY_ID_NR_OF; key_id++)
            {
                srv_bt_ui_key_status[key_id] = 0;
            }
            break;

        default:

            // Serial.print(F("SRV_UI_BT: Received command: "));
            // Serial.println(cmd);
            size_t key_id = srv_ui_bt_get_key_id(cmd);

            if (key_id < SRV_UI_BT_KEY_ID_NR_OF && key_id >= 0)
            {
                // increment the key status x2 (dec at the end of the loop)
                srv_bt_ui_key_status[key_id] += srv_bt_ui_key_inc[key_id];
                if (srv_ui_bt_roll_back_mode == SRV_UI_BT_ROLLBACK_ENABLED)
                {
                    srv_bt_ui_key_status[key_id] += srv_bt_ui_key_inc[key_id];
                }

#ifdef SRV_UI_BT_DEBUG
                Serial.print(F("SRV_UI_BT: Received command: "));
                Serial.println(cmd);
                Serial.print(F("SRV_UI_BT: KeyID: "));
                Serial.println(key_id);
                Serial.print(F("SRV_UI_BT: KeyID Status: "));
                Serial.println(srv_bt_ui_key_status[key_id]);
#endif
            }
            else
            {
                Serial.print(F("SRV_UI_BT: Unknown command: "));
                Serial.println(cmd);
            }
            break;
        }
    }
    // decrement the key status for all keys at the end of the loop
    for (uint8_t key_id = 0; key_id < SRV_UI_BT_KEY_ID_NR_OF; key_id++)
    {

        if (srv_ui_bt_roll_back_mode == SRV_UI_BT_ROLLBACK_ENABLED)
        {
            srv_bt_ui_key_status[key_id] -= srv_bt_ui_key_dec[key_id];
        }
    }

    // limit the key status
    for (uint8_t key_id = 0; key_id < SRV_UI_BT_KEY_ID_NR_OF; key_id++)
    {
        if (srv_bt_ui_key_status[key_id] > srv_bt_ui_key_status_max[key_id])
        {
            srv_bt_ui_key_status[key_id] = srv_bt_ui_key_status_max[key_id];
        }
        else if (srv_bt_ui_key_status[key_id] < srv_bt_ui_key_status_min[key_id])
        {
            srv_bt_ui_key_status[key_id] = srv_bt_ui_key_status_min[key_id];
        }
    }

    srv_ui_bt_power =
        srv_bt_ui_key_status[SRV_UI_BT_KEY_ID_FORWARD] +
        srv_bt_ui_key_status[SRV_UI_BT_KEY_ID_FORWARD_LEFT] +
        srv_bt_ui_key_status[SRV_UI_BT_KEY_ID_FORWARD_RIGHT] -
        srv_bt_ui_key_status[SRV_UI_BT_KEY_ID_BACKWARD] -
        srv_bt_ui_key_status[SRV_UI_BT_KEY_ID_BACKWARD_LEFT] -
        srv_bt_ui_key_status[SRV_UI_BT_KEY_ID_BACKWARD_RIGHT];

    srv_ui_bt_steering =
        srv_bt_ui_key_status[SRV_UI_BT_KEY_ID_RIGHT] +
        srv_bt_ui_key_status[SRV_UI_BT_KEY_ID_FORWARD_RIGHT] +
        srv_bt_ui_key_status[SRV_UI_BT_KEY_ID_BACKWARD_RIGHT] -
        srv_bt_ui_key_status[SRV_UI_BT_KEY_ID_LEFT] -
        srv_bt_ui_key_status[SRV_UI_BT_KEY_ID_FORWARD_LEFT] -
        srv_bt_ui_key_status[SRV_UI_BT_KEY_ID_BACKWARD_LEFT];
}

float srv_ui_bt_get_key_status(uint8_t key_id)
{
    return srv_bt_ui_key_status[key_id];
}

void srv_ui_bt_set_key_status_max(uint8_t key_id, float max)
{
    srv_bt_ui_key_status_max[key_id] = max;
}

void srv_ui_bt_set_key_inc(uint8_t key_id, float inc)
{
    srv_bt_ui_key_inc[key_id] = inc;
}

void srv_ui_bt_set_key_dec(uint8_t key_id, float dec)
{
    srv_bt_ui_key_dec[key_id] = dec;
}

int16_t srv_ui_bt_get_key_id(char key)
{
    for (uint8_t key_id = 0; key_id < SRV_UI_BT_KEY_ID_NR_OF; key_id++)
    {
        if (srv_bt_ui_key_char[key_id] == key)
        {
            return key_id;
        }
    }
    return -1;
}

void srv_ui_bt_report()
{
    Serial.print(F("SRV_UI_BT Rep key: "));
    for (uint8_t key_id = 0; key_id < SRV_UI_BT_KEY_ID_NR_OF; key_id++)
    {
        Serial.print(srv_bt_ui_key_char[key_id]);
        Serial.print(':');
        Serial.print(srv_bt_ui_key_status[key_id]);
        Serial.print(' ');
    }
    Serial.println();

    Serial.print(F("SRV_UI_BT Rep Power: "));

    Serial.print(srv_ui_bt_get_power());
    Serial.print(F(" Steering:"));
    Serial.print(srv_ui_bt_get_steering());

    Serial.println();
}

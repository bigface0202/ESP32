#include <Arduino.h>
#include <WiFi.h>
const char *ssid = "ESP32-WiFi"; //SSID of server
const char *pass = "esp32wifi";  //PW of server
static WiFiClient client;        //Declear client

uint8_t value = 0;
/*------------------------------------------------------*/
//For searial connection with Unity
int Unity_signal;

//For stop the PGM actuation by hand
int Kill_switch = 25;
int Kill_switch_now;
int Kill_switch_past = 0;

//For PGM actuation by hand
int PGM_switch_1 = 26;
int PGM_switch_2 = 27;
int PGM_switch_3 = 32;
int PGM_switch_4 = 33;
int PGM_switch_5 = 4;

int PGM_switch_1_now;
int PGM_switch_1_past = 0;
int PGM_switch_2_now;
int PGM_switch_2_past = 0;
int PGM_switch_3_now;
int PGM_switch_3_past = 0;
int PGM_switch_4_now;
int PGM_switch_4_past = 0;
int PGM_switch_5_now;
int PGM_switch_5_past = 0;

void switchFunction()
{
    PGM_switch_1_now = digitalRead(PGM_switch_1);
    PGM_switch_2_now = digitalRead(PGM_switch_2);
    PGM_switch_3_now = digitalRead(PGM_switch_3);
    PGM_switch_4_now = digitalRead(PGM_switch_4);
    PGM_switch_5_now = digitalRead(PGM_switch_5);

    if (PGM_switch_1_past != PGM_switch_1_now)
    {
        if (PGM_switch_1_now == HIGH)
        {
            Serial.println("PGM1 HIGH");
            client.write('1');
            delay(1000);
        }
        PGM_switch_1_past = PGM_switch_1_now;
    }

    if (PGM_switch_2_past != PGM_switch_2_now)
    {
        if (PGM_switch_2_now == HIGH)
        {
            Serial.println("PGM2 HIGH");
            client.write('2');
            delay(1000);
        }
        PGM_switch_2_past = PGM_switch_2_now;
    }

    if (PGM_switch_3_past != PGM_switch_3_now)
    {
        if (PGM_switch_3_now == HIGH)
        {
            Serial.println("PGM3 HIGH");
            client.write('3');
            delay(1000);
        }
        PGM_switch_3_past = PGM_switch_3_now;
    }

    if (PGM_switch_4_past != PGM_switch_4_now)
    {
        if (PGM_switch_4_now == HIGH)
        {
            Serial.println("PGM4 HIGH");
            client.write('4');
            delay(1000);
        }
        PGM_switch_4_past = PGM_switch_4_now;
    }

    if (PGM_switch_5_past != PGM_switch_5_now)
    {
        if (PGM_switch_5_now == HIGH)
        {
            Serial.println("PGM5 HIGH");
            client.write('5');
            delay(1000);
        }
        PGM_switch_5_past = PGM_switch_5_now;
    }
}

void setup()
{
    Serial.begin(115200);
    WiFi.begin(ssid, pass); //Connect to server
    Serial.printf("\n");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(1000);
    }
    Serial.printf("\n");
    Serial.println("WiFi Connected");
    IPAddress ip(192, 168, 0, 9); //IP address of server
    client.connect(ip, 80);       //Connect to IP address and port number

    pinMode(Kill_switch, INPUT);
    pinMode(PGM_switch_1, INPUT);
    pinMode(PGM_switch_2, INPUT);
    pinMode(PGM_switch_3, INPUT);
    pinMode(PGM_switch_4, INPUT);
    pinMode(PGM_switch_5, INPUT);
}

void loop()
{
    Unity_signal = Serial.read();
    Kill_switch_now = digitalRead(Kill_switch);

    switchFunction();
    if (client.connected() == true)
    {
        if (Unity_signal == '0')
        {
            client.write('0');
        }
        else if (Unity_signal == '1')
        {
            client.write('1');
        }
        else if (Unity_signal == '2')
        {
            client.write('2');
        }
        else if (Unity_signal == '3')
        {
            client.write('3');
        }
        else if (Unity_signal == '4')
        {
            client.write('4');
        }
        else if (Unity_signal == '5')
        {
            client.write('5');
        }
        if (Kill_switch_past != Kill_switch_now)
        {
            if (Kill_switch_now == HIGH)
            {
                Serial.println("HIGH");
                client.write('0');
                delay(1000);
                exit(0);
            }
            Kill_switch_past = Kill_switch_now;
        }
    }
}
#include <Arduino.h>
#include <WiFi.h>

int BLE_LED_pin = 4;
int PGM_Valve_Pin1 = 32;
int PGM_Valve_Pin2 = 25;
int PGM_Valve_Pin3 = 33;
int PGM_Valve_Pin4 = 26;
int PGM_Valve_Pin5 = 27;

uint8_t value;

const char *ssid = "ESP32-WiFi2";          //SSID
const char *pass = "esp32wifi2";           //PW
const IPAddress ip(192, 168, 0, 9);       //IP address of server
const IPAddress subnet(255, 255, 255, 0); //Subnetmask
WiFiServer server(80);

void setup()
{
    Serial.begin(115200);
    //pin setup
    //When BLE connnection success, this pin is HIGH.
    pinMode(BLE_LED_pin, OUTPUT);
    //PGM_pin
    pinMode(PGM_Valve_Pin1, OUTPUT);
    pinMode(PGM_Valve_Pin2, OUTPUT);
    pinMode(PGM_Valve_Pin3, OUTPUT);
    pinMode(PGM_Valve_Pin4, OUTPUT);
    pinMode(PGM_Valve_Pin5, OUTPUT);

    WiFi.softAP(ssid, pass);           //Set the SSID and PW
    delay(100);                        //Delay to avoid the deconnection
    WiFi.softAPConfig(ip, ip, subnet); //Set IP address, Gateway, and Subnetmask
    IPAddress myIP = WiFi.softAPIP();  //WiFi start
    server.begin();                    //Server start
    Serial.println();
    /*各種情報を表示*/
    Serial.println("WiFi connected");
    Serial.print("SSID：");
    Serial.println(ssid);
    Serial.print("AP IP address：");
    Serial.println(myIP);
    Serial.println("Server start!");
}

void loop()
{
    WiFiClient client = server.available();
    if (client)
    {
        while (client.connected())
        {
            digitalWrite(BLE_LED_pin, HIGH);
            value = client.read();
            if (value == '0')
            {
                Serial.println(value);
                digitalWrite(PGM_Valve_Pin1, LOW);
                digitalWrite(PGM_Valve_Pin2, LOW);
                digitalWrite(PGM_Valve_Pin3, LOW);
                digitalWrite(PGM_Valve_Pin4, LOW);
                digitalWrite(PGM_Valve_Pin5, LOW);
            }
            else if (value == '1')
            {
                Serial.println(value);
                digitalWrite(PGM_Valve_Pin1, HIGH);
                digitalWrite(PGM_Valve_Pin2, LOW);
                digitalWrite(PGM_Valve_Pin3, LOW);
                digitalWrite(PGM_Valve_Pin4, LOW);
                digitalWrite(PGM_Valve_Pin5, LOW);
            }
            else if (value == '2')
            {
                Serial.println(value);
                digitalWrite(PGM_Valve_Pin1, HIGH);
                digitalWrite(PGM_Valve_Pin2, HIGH);
                digitalWrite(PGM_Valve_Pin3, LOW);
                digitalWrite(PGM_Valve_Pin4, LOW);
                digitalWrite(PGM_Valve_Pin5, LOW);
            }
            else if (value == '3')
            {
                Serial.println(value);
                digitalWrite(PGM_Valve_Pin1, HIGH);
                digitalWrite(PGM_Valve_Pin2, HIGH);
                digitalWrite(PGM_Valve_Pin3, HIGH);
                digitalWrite(PGM_Valve_Pin4, LOW);
                digitalWrite(PGM_Valve_Pin5, LOW);
            }
            else if (value == '4')
            {
                Serial.println(value);
                digitalWrite(PGM_Valve_Pin1, HIGH);
                digitalWrite(PGM_Valve_Pin2, HIGH);
                digitalWrite(PGM_Valve_Pin3, HIGH);
                digitalWrite(PGM_Valve_Pin4, HIGH);
                digitalWrite(PGM_Valve_Pin5, LOW);
            }
            else if (value == '5')
            {
                Serial.println(value);
                digitalWrite(PGM_Valve_Pin1, HIGH);
                digitalWrite(PGM_Valve_Pin2, HIGH);
                digitalWrite(PGM_Valve_Pin3, HIGH);
                digitalWrite(PGM_Valve_Pin4, HIGH);
                digitalWrite(PGM_Valve_Pin5, HIGH);
            }
        }
    }
}
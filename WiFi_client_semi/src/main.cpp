#include <Arduino.h>
#include <WiFi.h>
const char *ssid = "ESP32-WiFi3"; //SSID of server
const char *pass = "esp32wifi3";  //PW of server
static WiFiClient client;        //Declear client

int switchPin = 25;

/*------------------------------------------------------*/
int serialSignal;

void setup()
{
    Serial.begin(115200);
    WiFi.disconnect(true);
    WiFi.begin(ssid, pass); //Connect to server
    Serial.printf("\n");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(1000);
    }
    Serial.printf("\n");
    Serial.println("WiFi Connected");
    IPAddress ip(192, 168, 0, 10); //IP address of server
    client.connect(ip, 80);       //Connect to IP address and port number

    pinMode(switchPin, INPUT);
}

void loop()
{
    serialSignal = Serial.read();

    client.println("a");
}
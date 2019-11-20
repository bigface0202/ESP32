#include <Arduino.h>
#include <WiFi.h>
const char *ssid = "ESP32-WiFi3"; //SSID of server
const char *pass = "esp32wifi3";  //PW of server
static WiFiClient client;        //Declear client

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
}

void loop()
{
  if (Serial.available() > 0) {
    char serialSignal = Serial.read();
    if (serialSignal == '0') {
      client.println("a");
    }
    if (serialSignal == '1') {
      client.println("b");
    }
    if (serialSignal == '2') {
      client.println("c");
    }
    if (serialSignal == '3') {
      client.println("d");
    }
    if (serialSignal == '4') {
      client.println("e");
    }
    if (serialSignal == '5') {
      client.println("f");
    }
    if (serialSignal == '6') {
      client.println("g");
    }
    if (serialSignal == '7') {
      client.println("h");
    }
    if (serialSignal == '8') {
      client.println("i");
    }
    if (serialSignal == '9') {
      client.println("j");
    }
    if (serialSignal == 'a') {
      client.println("k");
    }
  }
}
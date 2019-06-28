#include <Arduino.h>
#include <WiFi.h>

int LED_pin = 4;

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
    pinMode(LED_pin, OUTPUT);
    
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

void ledChikaChika(){
    digitalWrite(LED_pin, LOW);
    delay(1000);
    digitalWrite(LED_pin, HIGH);
    delay(1000);
}

void loop()
{
    WiFiClient client = server.available();
    if (client)
    {
        while (client.connected())
        {
            //When WiFi connnection success, this pin is HIGH.
            digitalWrite(LED_pin, HIGH);
            value = client.read();
            if (value == '0')
            {
                digitalWrite(LED_pin, LOW);
            }else if (value == '1')
            {
                ledChikaChika();
            }else if (value == '2')
            {
                ledChikaChika();
                ledChikaChika();
            }else if (value == '3')
            {
                ledChikaChika();
                ledChikaChika();
                ledChikaChika();
            }else if (value == '4')
            {
                ledChikaChika();
                ledChikaChika();
                ledChikaChika();
                ledChikaChika();
            }
            
        }
    }
}
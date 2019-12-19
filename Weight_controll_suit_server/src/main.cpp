#include <Arduino.h>
#include <WiFi.h>

int LED_pin = 4;

// PGM pin
//Extension
int PGM_12 = 12, PGM_13 = 13, PGM_14 = 14, PGM_15 = 15, PGM_21 = 21;
//Flexion
int PGM_25 = 25, PGM_26 = 26, PGM_27 = 27, PGM_32 = 32, PGM_33 = 33;

char value;

const char *ssid = "ESP32-WiFi3";         //SSID
const char *pass = "esp32wifi3";          //PW
const IPAddress ip(192, 168, 0, 10);      //IP address of server
const IPAddress subnet(255, 255, 255, 0); //Subnetmask
WiFiServer server(80);

void releaseAllPGM()
{
  digitalWrite(PGM_12, LOW);
  digitalWrite(PGM_13, LOW);
  digitalWrite(PGM_14, LOW);
  digitalWrite(PGM_15, LOW);
  digitalWrite(PGM_21, LOW);
  digitalWrite(PGM_25, LOW);
  digitalWrite(PGM_26, LOW);
  digitalWrite(PGM_27, LOW);
  digitalWrite(PGM_32, LOW);
  digitalWrite(PGM_33, LOW);
}

void setup()
{
  Serial.begin(115200);
  //pin setup
  pinMode(LED_pin, OUTPUT);
  pinMode(PGM_12, OUTPUT);
  pinMode(PGM_13, OUTPUT);
  pinMode(PGM_14, OUTPUT);
  pinMode(PGM_15, OUTPUT);
  pinMode(PGM_21, OUTPUT);
  pinMode(PGM_25, OUTPUT);
  pinMode(PGM_26, OUTPUT);
  pinMode(PGM_27, OUTPUT);
  pinMode(PGM_32, OUTPUT);
  pinMode(PGM_33, OUTPUT);
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
  digitalWrite(LED_pin, LOW);
}

void loop()
{
  WiFiClient client = server.available();
  if (client)
  {
    Serial.println("New Client.");
    while (client.connected())
    {
      //When WiFi connnection success, this pin is HIGH.
      digitalWrite(LED_pin, HIGH);
      value = client.read();
      if (value == 'a')
      {
        digitalWrite(PGM_12, HIGH);
        digitalWrite(PGM_13, LOW);
        digitalWrite(PGM_14, LOW);
        digitalWrite(PGM_15, LOW);
        digitalWrite(PGM_21, LOW);
        digitalWrite(PGM_25, LOW);
      }
      else if (value == 'b')
      {
        digitalWrite(PGM_12, HIGH);
        digitalWrite(PGM_13, HIGH);
        digitalWrite(PGM_14, LOW);
        digitalWrite(PGM_15, LOW);
        digitalWrite(PGM_21, LOW);
        digitalWrite(PGM_25, LOW);
      }
      else if (value == 'c')
      {
        digitalWrite(PGM_12, HIGH);
        digitalWrite(PGM_13, HIGH);
        digitalWrite(PGM_14, HIGH);
        digitalWrite(PGM_15, LOW);
        digitalWrite(PGM_21, LOW);
        digitalWrite(PGM_25, LOW);
      }
      else if (value == 'd')
      {
        digitalWrite(PGM_12, LOW);
        digitalWrite(PGM_13, LOW);
        digitalWrite(PGM_14, LOW);
        digitalWrite(PGM_15, HIGH);
        digitalWrite(PGM_21, LOW);
        digitalWrite(PGM_25, LOW);
      }
      else if (value == 'e')
      {
        digitalWrite(PGM_12, LOW);
        digitalWrite(PGM_13, LOW);
        digitalWrite(PGM_14, LOW);
        digitalWrite(PGM_15, HIGH);
        digitalWrite(PGM_21, HIGH);
        digitalWrite(PGM_25, LOW);
      }
      else if (value == 'f')
      {
        digitalWrite(PGM_12, LOW);
        digitalWrite(PGM_13, LOW);
        digitalWrite(PGM_14, LOW);
        digitalWrite(PGM_15, HIGH);
        digitalWrite(PGM_21, HIGH);
        digitalWrite(PGM_25, HIGH);
      }
      else if (value == 'k')
      {
        releaseAllPGM();
      }
    }
  }
}

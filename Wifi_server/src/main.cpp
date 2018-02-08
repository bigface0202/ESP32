#include <Arduino.h>

#include <WiFi.h>

WiFiServer server(80);

const char ssid[] = "ESP32-WiFi";  // SSID
const char pass[] = "esp32wifi";   // password
int value = 0;

const int Inputpin1 = 4;
const int Inputpin2 = 5;

const IPAddress ip(192, 168, 20, 2);      // IP address
const IPAddress subnet(255, 255, 255, 0); // Subnetmusk

void setup() {
  Serial.begin(115200);

  WiFi.softAP(ssid, pass);           // Configuration of the SSID and password
  delay(100);
  WiFi.softAPConfig(ip, ip, subnet); // Configuration of IP address, gateway, subnetmusk

  IPAddress myIP = WiFi.softAPIP();  // Turn on WiFi
  server.begin();                    // Turn on the server

  /* 各種情報を表示 */
  Serial.print("SSID: ");
  Serial.println(ssid);
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  Serial.println("Server start!");
  pinMode(Inputpin1, INPUT);
  pinMode(Inputpin2, INPUT);
}

void loop() {
  WiFiClient client = server.available();
  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:text/html");
  client.println();
  client.println("<b>test</b>");
  client.print("<meta http-equiv=");
  client.print("refresh");
  client.print(" content=");
  client.print("1");
  client.print(">");
  client.println(value);
  value++;
  delay(500);
  /*if (client) {
    String currentLine = "";
    Serial.println("new client!");
    while (client.connected()) {
      if (client.available()) {
        if (currentLine.length() == 0) {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-type:text/html");
          client.println();
          client.println("hello!");
          /*if(digitalRead(Inputpin1) == LOW){
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.println("Good afternoon");
          }else if(digitalRead(Inputpin2) == LOW){
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.println("Good morning");
          }
          break;
        } else {
          currentLine = "";
        }
      }
    }

    // 接続が切れた場合
    client.stop();
    Serial.println("client disonnected");
  }
  */
}

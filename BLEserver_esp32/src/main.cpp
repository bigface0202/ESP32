//BLE server
#include "Arduino.h"
/*
    Based on Neil Kolban example for IDF: https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleServer.cpp
    Ported to Arduino ESP32 by Evandro Copercini
*/

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

#define SERVICE_UUID        "91bad492-b950-4226-aa2b-4ede9fa42f59"
#define CHARACTERISTIC_UUID "0d563a58-196a-48ce-ace2-dfec78acc814"

const int InputPin1 = 4;
const int InputPin2 = 5;

BLECharacteristic *pCharacteristic;
uint8_t value = 0;
void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE work!");

  BLEDevice::init("ESP32");
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);
  pCharacteristic = pService->createCharacteristic(
                    CHARACTERISTIC_UUID,
                    BLECharacteristic::PROPERTY_READ   |
                    BLECharacteristic::PROPERTY_WRITE  |
                    BLECharacteristic::PROPERTY_NOTIFY |
                    BLECharacteristic::PROPERTY_INDICATE
                  );

  pCharacteristic->setValue("Hello World says Neil");
  pService->start();
  pServer->getAdvertising()->addServiceUUID(BLEUUID(SERVICE_UUID));
  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->start();
  Serial.println("Characteristic defined! Now you can read it in your phone!");
  pinMode(InputPin1, INPUT);
  pinMode(InputPin2, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  //uint8_t TEST1 = 4, TEST2 = 5;
  pCharacteristic->setValue("0");
  if (digitalRead(InputPin1) == LOW){
    //Serial.printf("*** NOTIFY: %d ***\n", value);
    pCharacteristic->setValue("1");
    //pCharacteristic->notify();
    delay(30);
  }else if (digitalRead(InputPin2) == LOW){
    //Serial.printf("*** NOTIFY: %d ***\n", value);
    pCharacteristic->setValue("2");
    //pCharacteristic->notify();
    delay(30);

  }

  //Serial.printf("*** NOTIFY: %d ***\n", value);
  //pCharacteristic->setValue(&value, 3);
  //pCharacteristic->notify();
  //pCharacteristic->indicate();
  //value++;
  //delay(2000);
}

#include <Arduino.h>
/*BLE---------------------------------------------------*/
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#define SERVICE_UUID "91bad492-b950-4226-aa2b-4ede9fa42f59"
#define CHARACTERISTIC_UUID "0d563a58-196a-48ce-ace2-dfec78acc814"

BLECharacteristic *pCharacteristic;
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
            pCharacteristic->setValue("1");
            delay(1000);
        }
        PGM_switch_1_past = PGM_switch_1_now;
    }

    if (PGM_switch_2_past != PGM_switch_2_now)
    {
        if (PGM_switch_2_now == HIGH)
        {
            Serial.println("PGM2 HIGH");
            pCharacteristic->setValue("1");
            delay(1000);
        }
        PGM_switch_2_past = PGM_switch_2_now;
    }

    if (PGM_switch_3_past != PGM_switch_3_now)
    {
        if (PGM_switch_3_now == HIGH)
        {
            Serial.println("PGM3 HIGH");
            pCharacteristic->setValue("1");
            delay(1000);
        }
        PGM_switch_3_past = PGM_switch_3_now;
    }

    if (PGM_switch_4_past != PGM_switch_4_now)
    {
        if (PGM_switch_4_now == HIGH)
        {
            Serial.println("PGM4 HIGH");
            pCharacteristic->setValue("1");
            delay(1000);
        }
        PGM_switch_4_past = PGM_switch_4_now;
    }

    if (PGM_switch_5_past != PGM_switch_5_now)
    {
        if (PGM_switch_5_now == HIGH)
        {
            Serial.println("PGM5 HIGH");
            pCharacteristic->setValue("1");
            delay(1000);
        }
        PGM_switch_5_past = PGM_switch_5_now;
    }
}

void setup()
{
    Serial.begin(115200);
    /*BLE-------------------------------------------------*/
    Serial.println("Starting BLE work!");

    BLEDevice::init("ESP32");
    BLEServer *pServer = BLEDevice::createServer();
    BLEService *pService = pServer->createService(SERVICE_UUID);
    pCharacteristic = pService->createCharacteristic(
        CHARACTERISTIC_UUID,
        BLECharacteristic::PROPERTY_READ |
            BLECharacteristic::PROPERTY_WRITE |
            BLECharacteristic::PROPERTY_NOTIFY |
            BLECharacteristic::PROPERTY_INDICATE);

    pCharacteristic->setValue("Hello World says Neil");
    pService->start();
    pServer->getAdvertising()->addServiceUUID(BLEUUID(SERVICE_UUID));
    BLEAdvertising *pAdvertising = pServer->getAdvertising();
    pAdvertising->start();
    Serial.println("Characteristic defined! Now you can read it in your phone!");
    /*---------------------------------------------------*/

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

    if (Unity_signal == '0')
    {
        pCharacteristic->setValue("0");
    }
    else if (Unity_signal == '1')
    {
        pCharacteristic->setValue("1");
    }
    else if (Unity_signal == '2')
    {
        pCharacteristic->setValue("2");
    }
    else if (Unity_signal == '3')
    {
        pCharacteristic->setValue("3");
    }
    else if (Unity_signal == '4')
    {
        pCharacteristic->setValue("4");
    }
    else if (Unity_signal == '5')
    {
        pCharacteristic->setValue("5");
    }
    if (Kill_switch_past != Kill_switch_now)
    {
        if (Kill_switch_now == HIGH)
        {
            Serial.println("HIGH");
            pCharacteristic->setValue("0");
            delay(1000);
            exit(0);
        }
        Kill_switch_past = Kill_switch_now;
    }
}
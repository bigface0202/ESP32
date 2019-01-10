#include <Arduino.h>
#include "BLEDevice.h"
//BLE setup
// The remote service we wish to connect to.
static BLEUUID serviceUUID("91bad492-b950-4226-aa2b-4ede9fa42f59");
// The characteristic of the remote service we are interested in.
static BLEUUID charUUID("0d563a58-196a-48ce-ace2-dfec78acc814");

static BLEAddress *pServerAddress;
static boolean doConnect = false;
static boolean connected = false;
static BLERemoteCharacteristic *pRemoteCharacteristic;

int BLE_LED_pin = 4;
int PGM_Valve_Pin1 = 32;
int PGM_Valve_Pin2 = 25;
int PGM_Valve_Pin3 = 33;
int PGM_Valve_Pin4 = 26;
int PGM_Valve_Pin5 = 27;

static void notifyCallback(
    BLERemoteCharacteristic *pBLERemoteCharacteristic,
    uint8_t *pData,
    size_t length,
    bool isNotify)
{
    Serial.print("Notify callback for characteristic ");
    Serial.print(pBLERemoteCharacteristic->getUUID().toString().c_str());
    Serial.print(" of data length ");
    Serial.println(length);
    Serial.println(long(pData));
}

bool connectToServer(BLEAddress pAddress)
{
    Serial.print("Forming a connection to ");
    Serial.println(pAddress.toString().c_str());

    BLEClient *pClient = BLEDevice::createClient();
    Serial.println(" - Created client");

    // Connect to the remove BLE Server.
    pClient->connect(pAddress);
    Serial.println(" - Connected to server");

    // Obtain a reference to the service we are after in the remote BLE server.
    BLERemoteService *pRemoteService = pClient->getService(serviceUUID);
    if (pRemoteService == nullptr)
    {
        Serial.print("Failed to find our service UUID: ");
        Serial.println(serviceUUID.toString().c_str());
        return false;
    }
    Serial.println(" - Found our service");

    // Obtain a reference to the characteristic in the service of the remote BLE server.
    pRemoteCharacteristic = pRemoteService->getCharacteristic(charUUID);
    if (pRemoteCharacteristic == nullptr)
    {
        Serial.print("Failed to find our characteristic UUID: ");
        Serial.println(charUUID.toString().c_str());
        return false;
    }
    Serial.println(" - Found our characteristic");

    // Read the value of the characteristic.
    std::string value = pRemoteCharacteristic->readValue();
    Serial.print("The characteristic value was: ");
    Serial.println(value.c_str());

    pRemoteCharacteristic->registerForNotify(notifyCallback);
}
/**
 * Scan for BLE servers and find the first one that advertises the service we are looking for.
 */
class MyAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks
{
    /**
   * Called for each advertising BLE server.
   */
    void onResult(BLEAdvertisedDevice advertisedDevice)
    {
        Serial.print("BLE Advertised Device found: ");
        Serial.println(advertisedDevice.toString().c_str());

        // We have found a device, let us now see if it contains the service we are looking for.
        if (advertisedDevice.haveServiceUUID() && advertisedDevice.getServiceUUID().equals(BLEUUID(serviceUUID)))
        {

            //
            Serial.print("Found our device!  address: ");
            advertisedDevice.getScan()->stop();

            pServerAddress = new BLEAddress(advertisedDevice.getAddress());
            doConnect = true;

        } // Found our server
    }     // onResult
};

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

    /*-- BLE setup --*/
    Serial.println("Starting Arduino BLE Client application...");
    BLEDevice::init("");

    // Retrieve a Scanner and set the callback we want to use to be informed when we
    // have detected a new device.  Specify that we want active scanning and start the
    // scan to run for 30 seconds.
    BLEScan *pBLEScan = BLEDevice::getScan();
    pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
    pBLEScan->setActiveScan(true);
    pBLEScan->start(30);
}

void loop()
{
    // If the flag "doConnect" is true then we have scanned for and found the desired
    // BLE Server with which we wish to connect.  Now we connect to it.  Once we are
    // connected we set the connected flag to be true.
    if (doConnect == true)
    {
        if (connectToServer(*pServerAddress))
        {
            Serial.println("We are now connected to the BLE Server.");
            connected = true;
        }
        else
        {
            Serial.println("We have failed to connect to the server; there is nothin more we will do.");
        }
        doConnect = false;
        digitalWrite(BLE_LED_pin, LOW);
    }

    // If we are connected to a peer BLE Server, update the characteristic each time we are reached
    // with the current time since boot.
    if (connected)
    {
        digitalWrite(BLE_LED_pin, HIGH);
        std::string value = pRemoteCharacteristic->readValue();
        if (value.c_str() == std::string("0"))
        {
            Serial.println(value.c_str());
            digitalWrite(PGM_Valve_Pin1, LOW);
            digitalWrite(PGM_Valve_Pin2, LOW);
            digitalWrite(PGM_Valve_Pin3, LOW);
            digitalWrite(PGM_Valve_Pin4, LOW);
            digitalWrite(PGM_Valve_Pin5, LOW);
        }
        else if (value.c_str() == std::string("1"))
        {
            Serial.println(value.c_str());
            digitalWrite(PGM_Valve_Pin1, HIGH);
            digitalWrite(PGM_Valve_Pin2, LOW);
            digitalWrite(PGM_Valve_Pin3, LOW);
            digitalWrite(PGM_Valve_Pin4, LOW);
            digitalWrite(PGM_Valve_Pin5, LOW);
        }
        else if (value.c_str() == std::string("2"))
        {
            Serial.println(value.c_str());
            digitalWrite(PGM_Valve_Pin1, HIGH);
            digitalWrite(PGM_Valve_Pin2, HIGH);
            digitalWrite(PGM_Valve_Pin3, LOW);
            digitalWrite(PGM_Valve_Pin4, LOW);
            digitalWrite(PGM_Valve_Pin5, LOW);
        }
        else if (value.c_str() == std::string("3"))
        {
            Serial.println(value.c_str());
            digitalWrite(PGM_Valve_Pin1, HIGH);
            digitalWrite(PGM_Valve_Pin2, HIGH);
            digitalWrite(PGM_Valve_Pin3, HIGH);
            digitalWrite(PGM_Valve_Pin4, LOW);
            digitalWrite(PGM_Valve_Pin5, LOW);
        }
        else if (value.c_str() == std::string("4"))
        {
            Serial.println(value.c_str());
            digitalWrite(PGM_Valve_Pin1, HIGH);
            digitalWrite(PGM_Valve_Pin2, HIGH);
            digitalWrite(PGM_Valve_Pin3, HIGH);
            digitalWrite(PGM_Valve_Pin4, HIGH);
            digitalWrite(PGM_Valve_Pin5, LOW);
        }
        else if (value.c_str() == std::string("5"))
        {
            Serial.println(value.c_str());
            digitalWrite(PGM_Valve_Pin1, HIGH);
            digitalWrite(PGM_Valve_Pin2, HIGH);
            digitalWrite(PGM_Valve_Pin3, HIGH);
            digitalWrite(PGM_Valve_Pin4, HIGH);
            digitalWrite(PGM_Valve_Pin5, HIGH);
        }
    }
}
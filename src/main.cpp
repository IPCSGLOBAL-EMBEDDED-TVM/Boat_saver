#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

BLEScan *pBLEScan;

class MyAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks
{
    void onResult(BLEAdvertisedDevice advertisedDevice)
    {
        String address = advertisedDevice.getAddress().toString().c_str();

        if (address.equalsIgnoreCase("23:08:07:10:1B:49"))
        {
            Serial.print("Fire-Boltt 130 RSSI: ");
            Serial.print(advertisedDevice.getRSSI());
            Serial.println(" dBm");
        }
    }
};

void setup()
{
    Serial.begin(115200);
    delay(1000);

    Serial.println("ESP32 BLE Scanner");

    BLEDevice::init("");

    pBLEScan = BLEDevice::getScan();

    pBLEScan->setAdvertisedDeviceCallbacks(
        new MyAdvertisedDeviceCallbacks()
    );

    pBLEScan->setActiveScan(true);
    pBLEScan->setInterval(100);
    pBLEScan->setWindow(99);
}

void loop()
{
    Serial.println();
    Serial.println("Scanning...");

    pBLEScan->start(5, false);

    Serial.print("Devices found: ");
    Serial.println(pBLEScan->getResults().getCount());

    pBLEScan->clearResults();

    delay(2000);
}
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include "SHTC3-SOLDERED.h"
#include "LTR-507-Light-And-Proximity-Sensor-SOLDERED.h"


#define SERVICE_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914b"

#define CHARACTERISTIC_UUID_1 "beb5483e-36e1-4688-b7f5-ea07361b26a8"
#define CHARACTERISTIC_UUID_2 "beb5483e-36e1-4688-b7f5-ea07361b26a9"
#define CHARACTERISTIC_UUID_3 "beb5483e-36e1-4688-b7f5-ea07361b26a0"
#define CHARACTERISTIC_UUID_4 "beb5483e-36e1-4688-b7f5-ea07361b26a1"
#define CHARACTERISTIC_UUID_5 "beb5483e-36e1-4688-b7f5-ea07361b26a5"  

BLEServer *pServer;
BLEService *pService;
BLECharacteristic *pCharacteristic1;  
BLECharacteristic *pCharacteristic2;  
BLECharacteristic *pCharacteristic3;
BLECharacteristic *pCharacteristic4;
BLECharacteristic *pCharacteristic5;

LTR507 sensor;
SHTC3 shtcSensor;



int characteristicValue1 = 0;
int characteristicValue2 = 0;
int characteristicValue3 = 0;
int characteristicValue4 = 0;
int characteristicValue5 = 0;

uint16_t lightReading = 80;

class MyServerCallbacks : public BLEServerCallbacks {
  void onConnect(BLEServer *pServer) {

  }

  void onDisconnect(BLEServer *pServer) {

  }
};

class MyCallbacks1 : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic) {

    std::string value = pCharacteristic->getValue();
    if (value.length() >= sizeof(uint16_t)) {
      uint16_t newValue = *(uint16_t *)(value.data());
      characteristicValue1 = newValue;
      Serial.println("Characteristic value 1 changed to: " + String(characteristicValue1));
    }
  }
};

class MyCallbacks2 : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic) {

    std::string value = pCharacteristic->getValue();
    if (value.length() >= sizeof(uint16_t)) {
      uint16_t newValue = *(uint16_t *)(value.data());
      characteristicValue2 = newValue;
      Serial.println("Characteristic value 2 changed to: " + String(characteristicValue2));
    }
  }
};

class MyCallbacks3 : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic) {

    std::string value = pCharacteristic->getValue();
    if (value.length() >= sizeof(uint16_t)) {
      uint16_t newValue = *(uint16_t *)(value.data());
      characteristicValue3 = newValue;
      Serial.println("Characteristic value 3 changed to: " + String(characteristicValue3));
    }
  }
};

class MyCallbacks4 : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic) {
    std::string value = pCharacteristic->getValue();
    if (value.length() >= sizeof(uint16_t)) {
      uint16_t newValue = *(uint16_t *)(value.data());
      characteristicValue4 = newValue;
      Serial.println("Characteristic value 4 changed to: " + String(characteristicValue4));
    }
  }
};


class MyCallbacks5 : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic) {
  
    std::string value = pCharacteristic->getValue();
    if (value.length() >= sizeof(uint16_t)) {
      uint16_t newValue = *(uint16_t *)(value.data());
      characteristicValue5 = newValue;
      Serial.println("Characteristic value 5 changed to: " + String(characteristicValue5));
    }
  }
};

void setup() {
  Serial.begin(115200);
  sensor.init();
  pinMode(2, INPUT);
  pinMode(4, INPUT);
  shtcSensor.begin();

  BLEDevice::init("ICSE-FER Sensor 1");

  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  pService = pServer->createService(BLEUUID(SERVICE_UUID), 32);

  pCharacteristic1 = pService->createCharacteristic(
    CHARACTERISTIC_UUID_1,
    BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_NOTIFY);

  pCharacteristic1->setValue((uint8_t *)&characteristicValue1, 1);
  pCharacteristic1->setCallbacks(new MyCallbacks1());

  pCharacteristic1->addDescriptor(new BLE2902());


  pCharacteristic2 = pService->createCharacteristic(
    CHARACTERISTIC_UUID_2,
    BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_NOTIFY);

  pCharacteristic2->setValue((uint8_t *)&characteristicValue2, 1);
  pCharacteristic2->setCallbacks(new MyCallbacks2());

  pCharacteristic2->addDescriptor(new BLE2902());


  pCharacteristic3 = pService->createCharacteristic(
    CHARACTERISTIC_UUID_3,
    BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_NOTIFY);

  pCharacteristic3->setValue((uint8_t *)&characteristicValue3, 1);
  pCharacteristic3->setCallbacks(new MyCallbacks3());

  pCharacteristic3->addDescriptor(new BLE2902());


  pCharacteristic4 = pService->createCharacteristic(
    CHARACTERISTIC_UUID_4,
    BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_NOTIFY);

  pCharacteristic4->setValue((uint8_t *)&characteristicValue4, 1);
  pCharacteristic4->setCallbacks(new MyCallbacks4());

  pCharacteristic4->addDescriptor(new BLE2902());


  pCharacteristic5 = pService->createCharacteristic(
    CHARACTERISTIC_UUID_5,
    BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_NOTIFY);

  pCharacteristic5->setValue((uint8_t *)&characteristicValue5, 1);
  pCharacteristic5->setCallbacks(new MyCallbacks5());

  pCharacteristic5->addDescriptor(new BLE2902());

  pService->start();


  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);  
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
}

void loop() {
  shtcSensor.sample();
  uint16_t water_reading = 1230;
  uint16_t lightReading = 1231;
  uint16_t newReading1 = 1232;
  uint16_t newReading2 = 1233;
  uint16_t newReading3 = 1234;

  int tempReading = shtcSensor.readTempC();
  newReading1 = tempReading;

  int humidityReading = shtcSensor.readHumidity();
  newReading2 = humidityReading;

  newReading3 = analogRead(4);

  lightReading = sensor.getLightIntensity();
  water_reading = analogRead(2);


  pCharacteristic1->setValue((uint8_t *)&lightReading, sizeof(uint16_t));
  pCharacteristic1->notify();

  pCharacteristic2->setValue((uint8_t *)&water_reading, sizeof(uint16_t));
  pCharacteristic2->notify();


  pCharacteristic3->setValue((uint8_t *)&newReading1, sizeof(uint16_t));
  pCharacteristic3->notify();

  pCharacteristic4->setValue((uint8_t *)&newReading2, sizeof(uint16_t));
  pCharacteristic4->notify();

  pCharacteristic5->setValue((uint8_t *)&newReading3, sizeof(uint16_t));
  pCharacteristic5->notify();

  delay(500);
}

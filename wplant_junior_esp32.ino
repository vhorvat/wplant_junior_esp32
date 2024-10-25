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

void controlLED(int reading) {
  if (reading < 100) {
    digitalWrite(6, HIGH); 
  } else {
    digitalWrite(6, LOW);
  }
}

void setup() {
  Serial.begin(115200);
  sensor.init();
  pinMode(2, INPUT);  //PIN senzor vlage
  pinMode(4, INPUT); //PIN pH senzor

  pinMode(6, OUTPUT); //LED
  
  shtcSensor.begin();


  //BLE Setup and charactristics
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
  uint16_t light_reading = 1231;
  uint16_t temperature_reading = 1232;
  uint16_t humidity_reading = 1233;
  uint16_t pH_reading = 1234;

  int tempReading = shtcSensor.readTempC();
  int humidityReading = shtcSensor.readHumidity();

  water_reading = analogRead(2);
  pH_reading = analogRead(4);
  light_reading = sensor.getLightIntensity();

  temperature_reading = tempReading;
  humidity_reading = humidityReading;

  controlLED(light_reading);

  Serial.println("Očitanje vlage tla %d", water_reading);
  Serial.println("Očitanje vlage zraka %d", humidityReading);
  Serial.println("Očitanje temperature %d", tempReading);
  Serial.println("Očitanje svjetlosti %d", light_reading);
  Serial.println("Očitanje pH vrijednosti %d", pH_reading);


  //BLE Advertise
  pCharacteristic1->setValue((uint8_t *)&light_reading, sizeof(uint16_t));  //karakteristika za svjetlost
  pCharacteristic1->notify();

  pCharacteristic2->setValue((uint8_t *)&water_reading, sizeof(uint16_t)); //karakteristika za vlaznost tla
  pCharacteristic2->notify();

  pCharacteristic3->setValue((uint8_t *)&temperature_reading, sizeof(uint16_t)); //karakteristika za temepraturu zraka
  pCharacteristic3->notify();

  pCharacteristic4->setValue((uint8_t *)&humidity_reading, sizeof(uint16_t)); //karakteristika za vlagu zraka
  pCharacteristic4->notify();

  pCharacteristic5->setValue((uint8_t *)&pH_reading, sizeof(uint16_t)); //karakteristika za pH vrijednost
  pCharacteristic5->notify();

  delay(500);
}

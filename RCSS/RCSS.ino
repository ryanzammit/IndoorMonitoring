


//"RBL_nRF8001.h/spi.h/boards.h" is needed in every new project
#include <boards.h>
#include <string.h>
#include <Adafruit_BME280.h>
#include <RBL_nRF8001.h>
#include <RBL_services.h>
#include <SPI.h>
#include <EddystoneBeacon.h>

Adafruit_BME280 bme;

#define EDDYSTONE_BEACON_REQ   6
#define EDDYSTONE_BEACON_RDY   7
#define EDDYSTONE_BEACON_RST   4

EddystoneBeacon eddystoneBeacon = EddystoneBeacon(EDDYSTONE_BEACON_REQ, EDDYSTONE_BEACON_RDY, EDDYSTONE_BEACON_RST);

void setup() {
  Serial.begin(9600);
  delay(1000);
  ble_begin();
  bme.begin();
  eddystoneBeacon.setLocalName("test");
}

void loop() {
    // degree celsius
    float temperature = bme.readTemperature();
    // % relative humidity
    float humidity = bme.readHumidity();
    // pascal
    float pressure = bme.readPressure();
    // voltage (no useable value without threshold)
    float concentrationGases = (float) analogRead(A0)/1024*5.0; //mq5
    // voltage (no useable value without threshold)
    float combustibleGases = (float) analogRead(A1)/1024*5.0; //mq2
    // voltage (no useable value without threshold)
    float airQuality = (float) analogRead(A2)/1024*5.0; //mq-135

    char sConcentrationGases[10];
    char sCombustibleGases[10];
    char sAirQuality[10];
    
    dtostrf(concentrationGases, 1, 6, sConcentrationGases);
    dtostrf(combustibleGases, 1, 6, sCombustibleGases);
    dtostrf(airQuality, 1, 6, sAirQuality);

    String json = "{\"version\":\"1.0.0\",\"sensors\":{\"temperature\":" + String(temperature) +
                  ",\"humidity\":" + String(humidity) +
                  ",\"pressure\":" + String(pressure) +
                  ",\"concentrationGases\":" + String(sConcentrationGases) +
                  ",\"combustibleGases\":" + String(sCombustibleGases) + 
                  ",\"airQuality\":" + String(sAirQuality) + 
                  "}}";

    Serial.println(json);                  
//    for(char& c : json){
//      ble_write(c);
//    }
//  
//
//  ble_do_events();

  eddystoneBeacon.begin(-18, "{\"sensors\":{\"temp\":\"21\"}}"); // power, URI
  eddystoneBeacon.loop();
  // delay so the arduino doesnt burn
  delay(3000);
}


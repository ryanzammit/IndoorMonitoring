/*

Copyright (c) 2012-2014 RedBearLab

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

/*
 *    HelloWorld
 *
 *    HelloWorld sketch, work with the Chat iOS/Android App.
 *    It will send "Hello World" string to the App every 1 sec.
 *
 */

//"RBL_nRF8001.h/spi.h/boards.h" is needed in every new project
#include <SPI.h>
#include <EEPROM.h>
#include <boards.h>
#include <RBL_nRF8001.h>
#include <Adafruit_BME280.h>

Adafruit_BME280 bme;

void setup()
{
  ble_begin();  
  bme.begin();
  // Enable serial debug
  Serial.begin(57600);
}

unsigned char buf[16] = {0};
unsigned char len = 0;

void loop()
{
  if(ble_connected()){
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
    
    String string = "[" + String(temperature) + "|" + String(humidity) + "|" + String(pressure) + "|" + String(sConcentrationGases) + "|" + String(sCombustibleGases) + "|" + String(sAirQuality) + "]";

    for(char& c : string){
      ble_write(c);
    }

    
  }

  ble_do_events();

  // delay so the arduino doesnt burn
  delay(500);
}


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
#include <string.h>
#include <RBL_nRF8001.h>

void setup()
{
  //  
  // For BLE Shield and Blend:
  //   Default pins set to 9 and 8 for REQN and RDYN
  //   Set your REQN and RDYN here before ble_begin() if you need
  //
  // For Blend Micro:
  //   Default pins set to 6 and 7 for REQN and RDYN
  //   So, no need to set for Blend Micro.
  //
  //ble_set_pins(3, 2);
  
  // Set your BLE advertising name here, max. length 10
  //ble_set_name("My BLE");
  
  // Init. and start BLE library.
  ble_begin();
  
  // Enable serial debug
  Serial.begin(9600);
}

unsigned char buf[16] = {0};
unsigned char len = 0;

String floatToString2(float f){
  char temp[10];
  String s;
  
  // perform conversion
  dtostrf(f,1,2,temp);
    
  // create string object
  s = String(temp);
  
  return s;
}

void loop()
{
  if ( ble_connected() )
  {
    /*
    float temperature = 22.4;
    float humidity = 46.9;
    float pressure = 85.123;
    float smoke = 0;
    float oxygen = 0.21;
    float monoxide = 0.001;
    float dioxide = 0.005;
    */

    float airSensorVolt; 
    float smokeSensorVolt;
    float sensor3Volt;

    /*
    char sTemperature[10];
    char sHumidity[10];
    char sPressure[10];
    char sSmok[10];
    char sOxygen[10];
    char sMonoxide[10];
    char sDioxide[10];
    */
    
    char sAir[10];
    char sSmoke[10];
    char sSensor3[10];
    
    
    airSensorVolt = (float) analogRead(A0)/1024*5.0;
    smokeSensorVolt = (float) analogRead(A1)/1024*5.0;
    sensor3Volt = (float) analogRead(A2)/1024*5.0;
    
    Serial.println("");
    Serial.print("Air sensor volt = ");
    Serial.print(airSensorVolt);
    Serial.println("V");
    
    Serial.print("Smoke sensor volt = ");
    Serial.print(smokeSensorVolt);
    Serial.println("V");
    
    Serial.print("Sensor 3 volt = ");
    Serial.print(sensor3Volt);
    Serial.println("V");
    
    
/*    
    dtostrf(temperature, 1, 5, sTemperature);
    dtostrf(humidity, 1, 5, sHumidity);
    dtostrf(pressure, 1, 5, sPressure);
    dtostrf(smoke, 1, 0, sSmok);
    dtostrf(oxygen, 1, 5, sOxygen);
    dtostrf(monoxide, 1, 5, sMonoxide);
    dtostrf(dioxide, 1, 5, sDioxide);
*/

    dtostrf(airSensorVolt, 1, 5, sAir);
    dtostrf(smokeSensorVolt, 1, 5, sSmoke);
    dtostrf(sensor3Volt, 1, 5, sSensor3);

    String json = "this is supposed to be a very long string, where everything is made up and there are no points. sometimes the rabbit asks the cow, are you hungry, and the cow ansers yes and rips of a bunch of grass.";

    json = "{\"sensors\":{\"air\":" + String(sAir) + ",\"smoke\":" + String(sSmoke) + ",\"sensor3\":" + String(sSensor3) + "}}";
    
    /*"{version:1.0,sensors:{temperature:" + String(sTemperature) +
      ",humidity:" + String(sHumidity) +
      ",pressure:" + String(sPressure) +
      ",smoke:" + String(sSmoke) +
      ",atmosphere:{oxygen:" + String(sOxygen) +
      ",monoxide:" + String(sMonoxide) +
      ",dioxide:" + String(sDioxide) +
      "},time:00:00:00}}";
      */

    int i = 0;
    
    for(char& c : json){
      ble_write(c);

     // Serial.print("Stringsize: " + String(sizeof(json)) + "\r\n");

      i++;
      if(i % 20 == 0){
        i = 0;
        //
//        delay(1000);
      }
    }
  }

  ble_do_events();

  /*
  if ( ble_available() )
  {
    while ( ble_available() )
    {
      Serial.write(ble_read());
    }
    
    Serial.println();
  }
  */

  delay(3000);
}


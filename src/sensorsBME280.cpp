#include <Arduino.h>
#include "sensorsBME280.h"
#include "HTTPinit.h"
#include "json.h"


#define WALK 0  // // GPIO0 or D3 - what digital pin we're connected to


extern ESP8266WebServer HTTP;
TickerScheduler ts(3);

Adafruit_BME280 bme; // Датчик BME280 на интерфейсе I2C
Adafruit_CCS811 ccs;

float t;

void wetherSensor_init(){

    HTTP.on("/sensors.json", HTTP_GET, []() {

        HTTP.send(200, "application/json", sensorsJson); 
    });

   pinMode(WALK, OUTPUT); 

    Serial.println(F("BME280 test: "));
    if (! bme.begin(&Wire)) {
        Serial.println("Could not find a valid BME280 sensor, check wiring!");
        while (1);
    }else{
      ts.add(0, 2100, [&](void*){
        String t_str, p, h;
        t = bme.readTemperature()-2.3;
        p = bme.readPressure() / 100.0F/1.33322;
        t_str = t;
        // h = bme.readHumidity();

        jsonWrite(sensorsJson, "termo", t_str);
        // jsonWrite(sensorsJson, "humid", h);
        jsonWrite(sensorsJson, "pressure", p);
      }, nullptr, true);
    }

    digitalWrite(WALK, LOW);
    if(!ccs.begin()){
      Serial.println("Error sensor!");
    }else{
      ts.add(1, 5125, [&](void*){
        void ccs811();
      }, nullptr, true);
    }
    digitalWrite(WALK, HIGH);
}


void ccs811(){
  digitalWrite(WALK, LOW);
  delay(100);
  if(ccs.available()){
    if(!ccs.readData()){
      float eCO2 = ccs.geteCO2();
      float tvoc = ccs.getTVOC();

      jsonWrite(sensorsJson, "eCO2", eCO2);
      jsonWrite(sensorsJson, "tvoc", tvoc);
    }
    else{
     Serial.println("Error read ccs811 sensor!");
    }
  }
    delay(20);
    digitalWrite(WALK, HIGH);
}
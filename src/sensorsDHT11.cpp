#include "sensorsDHT11.h"
#include "json.h"
#include "HTTPinit.h"

extern ESP8266WebServer HTTP;

#define DHTPIN 4 // GPIO4 or D2 - what digital pin we're connected to
#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);

//   humidity => 0
//   temperature => 1
void initDht(void){
    HTTP.on("/sensors.json", HTTP_GET, []() {
      readDht (0);
      HTTP.send(200, "application/json", sensorsJson); 
    });

  dht.begin();
  // static uint16_t test = dht.getMinimumSamplingPeriod(); // Получаем минимальное значение между запросами данных с датчика 
}

int16_t readDht (int8_t who) {
  static int16_t t, h;
  if (who == 0){ 
    t = dht.readTemperature();
    h = dht.readHumidity();
    // Serial.print("termo: ");
    // Serial.print(t);
    jsonWrite(sensorsJson, "termo", t);
    jsonWrite(sensorsJson, "humid", h);
    // jsonWrite(sensorsJson, "pressure", 1008);
  }

  if (who == 1){ return h;}

  if (who == 2){ return t;}
}

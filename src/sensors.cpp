#include "sensors.h"
#include "json.h"
#include "HTTPinit.h"

#define DHTPIN 4 // GPIO4 or D2 - what digital pin we're connected to
#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);

//   humidity => 0
//   temperature => 1
void initDht(void){
   dht.begin();
}

int16_t readDht (bool who) {
  if (who == 0){ 
      return dht.readHumidity();
  }
  if (who == 1){
        int16_t t;
        t = dht.readTemperature();
        jsonWrite(sensorsJson, "termo", t);
        jsonWrite(sensorsJson, "humin", dht.readHumidity());
      return t;
  }
}
//    if (isnan(h) || isnan(t) || isnan(f)) {
//     Serial.println("Failed to read from DHT sensor!");
//     return;

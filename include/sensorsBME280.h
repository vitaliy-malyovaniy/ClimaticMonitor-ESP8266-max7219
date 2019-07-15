/* Подключение датчика по I2C шине 
   BME280      ESP8266
     SCL          D1
     SDA          D2 

     Adress BMP280  0x76
            BME280  0x58   
*/
#include <Wire.h>
#include "Adafruit_Sensor.h"
#include "Adafruit_BME280.h"
#include "Adafruit_CCS811.h"
#include "TickerScheduler.h"

#define SEALEVELPRESSURE_HPA (1013.25)

void wetherSensor_init(void);
void readBME(void);
void ccs811(void);

extern float t;
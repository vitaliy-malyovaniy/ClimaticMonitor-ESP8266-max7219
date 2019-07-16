/* Подключение датчика по I2C шине 
   BME280      ESP8266
     SCL          D1
     SDA          D2 

            Adress    Chip ID   
     BMP280  0x76      0x58
     BME280  0x76      0x60       
*/
#include <Wire.h>
#include "Adafruit_Sensor.h"
#include "Adafruit_BME280.h"
#include "Adafruit_CCS811.h"
#include "TickerScheduler.h"

#define SEALEVELPRESSURE_HPA (1013.25)

void wetherSensor_init(void);
void readBME280(void);
void ccs811(void);

extern float t;
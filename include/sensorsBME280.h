/* Подключение датчика по I2C шине 
   BME280      ESP8266
     SCL          D1
     SDA          D2 

            Adress    Chip ID   
     BMP280  0x76      0x58
     BME280  0x76      0x60       
*/
#include <Wire.h>
#include <SparkFunBME280.h>
#include <SparkFunCCS811.h>
#include "TickerScheduler.h"

#define SEALEVELPRESSURE_HPA (1013.25)
#define CCS811_ADDR 0x5A
// #define PIN_NOT_WAKE 5

void wetherSensor_init(void);
void readBME280(void);
void readCCS811(void);

void printSensorError(void);
void printInfoSerial(void);
void Charts_init(void);

extern float BMEtempC;
extern int16_t eCO2;
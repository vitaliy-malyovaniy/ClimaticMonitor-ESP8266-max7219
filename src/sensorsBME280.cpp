#include <Arduino.h>
#include "sensorsBME280.h"
#include "HTTPinit.h"
#include "json.h"

#define WALK 0  // // GPIO0 or D3 - what digital pin we're connected to

extern ESP8266WebServer HTTP;
TickerScheduler ts(3);
const uint8_t lengt=30; 
int16_t _CO2[lengt];
float _termo[lengt];

//Global sensor objects
CCS811 myCCS811(CCS811_ADDR);
BME280 myBME280;

float BMEtempC, BMEhumid;
int16_t eCO2;

// printDriverError декодирует тип CCS811Core :: status и печатает тип ошибки на последовательном терминале.
// Сохраните возвращаемое значение любой функции типа CCS811Core :: status, 
// затем перейдите к этой функции, чтобы увидеть, какой был результат
void printDriverError( CCS811Core::status errorCode ) {
  switch ( errorCode )
  {
    case CCS811Core::SENSOR_SUCCESS:
      Serial.println("SUCCESS");
      break;
    case CCS811Core::SENSOR_ID_ERROR:
      Serial.println("ID_ERROR");
      break;
    case CCS811Core::SENSOR_I2C_ERROR:
      Serial.println("I2C_ERROR");
      break;
    case CCS811Core::SENSOR_INTERNAL_ERROR:
      Serial.println("INTERNAL_ERROR");
      break;
    case CCS811Core::SENSOR_GENERIC_ERROR:
      Serial.println("GENERIC_ERROR");
      break;
    default:
      Serial.println("Unspecified error.");
  }
}

void wetherSensor_init(){

  HTTP.on("/sensors.json", HTTP_GET, []() {
      HTTP.send(200, "application/json", sensorsJson); 
  });

  Wire.begin();
  pinMode(WALK, OUTPUT); 
  digitalWrite(WALK, LOW);
  delay(80);
    //This begins the CCS811 sensor and prints error status of .begin()
  CCS811Core::status returnCode = myCCS811.begin();
  Serial.print("CCS811 begin exited with: ");
  //Pass the error code to a function to print the results
  printDriverError( returnCode );

  //Initialize BME280
  //For I2C, enable the following and disable the SPI section
  myBME280.settings.commInterface = I2C_MODE;
  myBME280.settings.I2CAddress = 0x76;
  myBME280.settings.runMode = 3; // Forced // 3 - Normal mode
  myBME280.settings.filter = 4;
  // myBME280.settings.tempOverSample = 5;
  myBME280.settings.tStandby = 0; // 0, 0.5ms //  1, 62.5ms //  2, 125ms //  3, 250ms //  4, 500ms //  5, 1000ms //  6, 10ms //  7, 20ms

  delay(10);  //Make sure sensor had enough time to turn on. BME280 requires 2ms to start up.
  myBME280.begin();
      if(!returnCode){                  // если CCS811Core = "SUCCESS"
        ts.add(0, 2500, [&](void*){
          static int j=0;
          if (j == 0){
            readBME280();
            j++;
          }else{
            readCCS811();
            j--;
          }
        }, nullptr, true);
      }else{
        Serial.println(">> Error sensor!  <<");
      }
    digitalWrite(WALK, HIGH);
}

void array_temp_eCO2(int16_t *array){ // массив временных данных для подсчета средних показаний после того как он будет заполнен
	const int8_t arrLength = 20;
  static int8_t i=0;
  static int32_t summa = 0;
  summa += eCO2;
  i++;
  
  if (i == arrLength){
    i=0;
    for (int j=lengt-1; j>0; j--){
      array[j] = array[j-1];
    }
    array[0] = summa / arrLength;
    summa=0;
  }
}

void array_temp_any(int16_t *array, int16_t item){ // массив временных данных для подсчета средних показаний после того как он будет заполнен
	const int8_t arrLength = 20;
  static int8_t i=0;
  static int32_t summa = 0;
  summa += item;
  i++;
  
  if (i == arrLength){
    i=0;
    for (int j=lengt-1; j>0; j--){
      array[j] = array[j-1];
    }
    array[0] = summa / arrLength;
    summa=0;
  }
}

void array_temp_any(float *array, float item){ // массив временных данных для подсчета средних показаний после того как он будет заполнен
	const int8_t arrLength = 20;
  static int8_t i=0;
  static float summa = 0;
  summa += item;
  i++;
  
  if (i == arrLength){
    i=0;
    for (int j=lengt-1; j>0; j--){
      array[j] = array[j-1];
    }
    array[0] = summa / arrLength;
    summa=0;
  }
}

void Charts_init() {
  HTTP.on("/graf.json", HTTP_GET, []() {
    String chart = graf((int16_t*) _CO2, (float*) _termo, lengt); //
    HTTP.send(200, "application/json", chart);
  });
        
  ts.add(2, 30000, [&](void*){   // каждые 30 секунд
  array_temp_any((int16_t*) _CO2, eCO2);
  array_temp_any((float*) _termo, BMEtempC);
  }, nullptr, true);
}

void readBME280(){
  float BMEpress;
  BMEtempC = myBME280.readTempC();
  BMEhumid = myBME280.readFloatHumidity();
  BMEpress = myBME280.readFloatPressure()/ 133.322;

  jsonWrite(sensorsJson, "termo", BMEtempC);
  jsonWrite(sensorsJson, "humid", BMEhumid);
  jsonWrite(sensorsJson, "pressure", BMEpress);

}

void readCCS811(){
  digitalWrite(WALK, LOW);
  delay(50);
  if (myCCS811.dataAvailable()) {
    float tvoc;
    //Calling this function updates the global tVOC and eCO2 variables
    myCCS811.readAlgorithmResults();

    //This sends the temperature data to the CCS811
    myCCS811.setEnvironmentalData(BMEhumid, BMEtempC);
    eCO2 = myCCS811.getCO2();
    tvoc = myCCS811.getTVOC();
 
    jsonWrite(sensorsJson, "eCO2", eCO2);
    jsonWrite(sensorsJson, "tvoc", tvoc);
 
  }else if (myCCS811.checkForStatusError()){
    //If the CCS811 found an internal error, print it.
    printSensorError();
  }
  digitalWrite(WALK, HIGH);
} 

void printInfoSerial()
{
  //getCO2() gets the previously read data from the library
  Serial.println("CCS811 data:");
  Serial.print(" CO2 concentration : ");
  Serial.print(myCCS811.getCO2());
  Serial.println(" ppm");

  //getTVOC() gets the previously read data from the library
  Serial.print(" TVOC concentration : ");
  Serial.print(myCCS811.getTVOC());
  Serial.println(" ppb");

  Serial.println("BME280 data:");
  Serial.print(" Temperature: ");
  Serial.print(myBME280.readTempC(), 2);
  Serial.println(" degrees C");

  Serial.print(" Pressure: ");
  Serial.print(myBME280.readFloatPressure(), 2);
  Serial.println(" Pa");

  Serial.print(" Altitude: ");
  Serial.print(myBME280.readFloatAltitudeMeters(), 2);
  Serial.println("m");

  Serial.print(" %RH: ");
  Serial.print(myBME280.readFloatHumidity(), 2);
  Serial.println(" %");

  Serial.println();
}

//printSensorError gets, clears, then prints the errors
//saved within the error register.
void printSensorError()
{
  uint8_t error = myCCS811.getErrorRegister();

  if ( error == 0xFF ) //comm error
  {
    Serial.println("Failed to get ERROR_ID register.");
  }
  else
  {
    Serial.print("Error: ");
    if (error & 1 << 5) Serial.print("HeaterSupply");
    if (error & 1 << 4) Serial.print("HeaterFault");
    if (error & 1 << 3) Serial.print("MaxResistance");
    if (error & 1 << 2) Serial.print("MeasModeInvalid");
    if (error & 1 << 1) Serial.print("ReadRegInvalid");
    if (error & 1 << 0) Serial.print("MsgInvalid");
    Serial.println();
  }
}
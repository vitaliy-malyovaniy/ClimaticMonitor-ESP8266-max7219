#include <Arduino.h>
#include "FSWebServer.h"
#include "WIFI.h"
#include "HTTPinit.h"

#include "max7219display.h"
#include "max7219displayTest.h"
#include "sensors.h"
#include "FileConfig.h"
#include "json.h"


extern ESP8266WebServer HTTP;
extern LedControl lc;

void setup()
{
  Serial.begin(115200);
// displayDemo();
// -------------------------------------
  FS_init();  //Запускаем файловую систему
  configSetup = readFile("configs.json", 4096); // считали файл configs.json и поместили в переменную "configSetup"
  delay(1000);
  Serial.println("");

  // записываем в "configJson" значение "SSDP" из "configSetup", чтобы применить
  // при инициализации SSDP и последующем отображении имени в ярлыке
  jsonWrite(configJson, "SSDP", jsonRead(configSetup, "SSDP"));

  WIFIinit();
  SSDP_init();  //Настраиваем и запускаем SSDP интерфейс
  HTTP_init(); // Настраиваем и запускаем HTTP интерфейс
    
  // max7219displayInit();
  // Serial.println("initialisation sensor DHT11...");
  initDht();
}

void loop()
{
  HTTP.handleClient(); // отслеживает присутствие клиента и доставляет запрошенную HTML-страницу
// Serial.println(" ");
// Serial.print("Huminity: ");
// Serial.println(readDht (0));
// delay(1500);
// Serial.print("Temperature: ");
// Serial.println(readDht (1));
    // printTwoNumb(readDht (1), 5);
    // printSymbolTermo();
    readDht (1);
    delay(150);

}

#include "FSWebServer.h"
#include "WIFI.h"
#include "HTTPinit.h"

#include "max7219display.h"
#include "max7219displayTest.h"
#include "sensors.h"

extern ESP8266WebServer HTTP;
extern LedControl lc;

void setup()
{
Serial.begin(115200);
// displayDemo();
// -------------------------------------
    FS_init();  //Запускаем файловую систему
    WIFIinit();
    SSDP_init();  //Настраиваем и запускаем SSDP интерфейс
    HTTP_init(); // Настраиваем и запускаем HTTP интерфейс
    
  max7219displayInit();
  Serial.println("initialisation sensor DHT11...");
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
    printTwoNumb(readDht (1), 5);
    printSymbolTermo();
    delay(2000);
}
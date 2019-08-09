#include "HTTPinit.h"
#include "WIFI.h"
// #include "sensorsDHT11.h"
#include "In-Out.h"
#include "json.h"
#include "FileConfig.h"

// Web интерфейс для устройства
ESP8266WebServer HTTP(80);

String configSetup = "{}"; // строка в которую ложится "копия" configs.json
String configJson = "{}";  
String sensorsJson = "{}"; // строка в которой собираются данные с датчиков


void HTTP_init() {
  // --------------------Выдаем данные configJson
  HTTP.on("/configs.json", HTTP_GET, []() {
    // outData();
    HTTP.send(200, "application/json", configSetup); 
  });
  
  HTTP.on("/ssid", handle_Set_Ssid);            // Установить имя и пароль роутера по запросу вида /ssid?ssid=home2&password=12345678
   
  HTTP.on("/restart", handle_Restart);          // Перезагрузка модуля по запросу вида /restart?device=ok
  // Запускаем HTTP сервер
  HTTP.begin();
}

void SSDP_init() {  // SSDP дескриптор
  Serial.print("Start SSDP ");
  String chipID = String( ESP.getChipId() ) + "-" + String( ESP.getFlashChipId() );
  HTTP.on("/description.xml", HTTP_GET, [](){
   SSDP.schema(HTTP.client());
  });

  // --------------------Получаем SSDP со страницы
  HTTP.on("/ssdp", HTTP_GET, []() {
    String ssdp = HTTP.arg("ssdp");
  // configJson=jsonWrite(configJson, "SSDP", ssdp);
  // configJson=jsonWrite(configSetup, "SSDP", ssdp);
  SSDP.setName(jsonRead(configSetup, "SSDP"));
  saveConfig();                 // Функция сохранения данных во Flash
  HTTP.send(200, "text/plain", "OK"); // отправляем ответ о выполнении
  });

  //Если версия  2.0.0 закаментируйте следующую строчку
  SSDP.setDeviceType("upnp:rootdevice");
  SSDP.setSchemaURL("description.xml");
  SSDP.setHTTPPort(80);
  SSDP.setName(jsonRead(configSetup, "SSDP"));
  SSDP.setSerialNumber(chipID);
  SSDP.setURL("/");
  SSDP.setModelName("xlooRoomClimatic");
  SSDP.setModelNumber(chipID + "/" + jsonRead(configSetup, "SSDP"));
  // SSDP.setModelURL("http://");
  SSDP.setManufacturer("Malyovaniy Vitaliy");
  // SSDP.setManufacturerURL("http://");
  SSDP.begin();
  Serial.println("- OK");
}

// Перезагрузка модуля по запросу вида http://192.168.0.101/restart?device=ok
void handle_Restart() {
  String restart = HTTP.arg("device");          // Получаем значение device из запроса
  Serial.print("String restart: ");
  Serial.println(restart);
  if (restart == "ok") {                         // Если значение равно Ок
    HTTP.send(200, "text / plain", "Restart - OK"); // Oтправляем ответ Reset OK
    ESP.restart();                                // перезагружаем модуль
  }
  else {                                        // иначе
    HTTP.send(200, "text / plain", "No Reset"); // Oтправляем ответ No Reset
  }
}

// Установка параметров для подключения к внешней AP по запросу вида http://192.168.0.101/ssid?ssid=home2&password=12345678
void handle_Set_Ssid () {
 _ssid = HTTP.arg("ssid");           // Получаем значение ssid из запроса сохраняем в глобальной переменной
 _password = HTTP.arg("password");   // Получаем значение password из запроса сохраняем в глобальной переменной
 //  saveConfig();                    // Функция сохранения данных во Flash пока пустая
 HTTP.send(200, "text/plain", "OK"); // отправляем ответ о выполнении
}

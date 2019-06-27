#include "HTTPinit.h"
#include "WIFI.h"
#include "sensors.h"
#include "In-Out.h"

// extern Adafruit_BME280 bme;

// Web интерфейс для устройства
ESP8266WebServer HTTP(80);
String jsonConfig = "{}";
String configJson = "{}";
String sensorsJson = "{}";
String setTimer;

void handle_ConfigJSON() {
  String root = "{}";  // Формировать строку для отправки в браузер json формат
  //{"SSDP":"SSDP-test","ssid":"home","password":"i12345678","ssidAP":"WiFi","passwordAP":"","ip":"192.168.0.101"}

  // Резервируем память для json обекта буфер может рости по мере необходимти, предпочтительно для ESP8266
  DynamicJsonBuffer jsonBuffer;
  //  вызовите парсер JSON через экземпляр jsonBuffer
  JsonObject& json = jsonBuffer.parseObject(root);
  // Заполняем поля json
  json["SSDP"] = SSDP_Name;
  json["ssidAP"] = _ssidAP;
  json["passwordAP"] = _passwordAP;
  json["ssid"] = _ssid;
  json["password"] = _password;
  json["ip"] = WiFi.localIP().toString();
  // Помещаем созданный json в переменную root
  Serial.println("response Configs.json");
  root = "";
  json.printTo(root);
  HTTP.send(200, "text/json", root);
}

void HTTP_init() {
  // --------------------Выдаем данные configJson
  HTTP.on("/config.live.json", HTTP_GET, []() {
    // outData();
    HTTP.send(200, "application/json", configJson); 
  });
  
  HTTP.on("/sensors.json", HTTP_GET, []() {
    Serial.println("response Sensor.json");
    // readSensor();
    HTTP.send(200, "application/json", sensorsJson); 
  });

  HTTP.on("/configs.json", handle_ConfigJSON);  // формирование configs.json страницы для передачи данных в web интерфейс
  // API для устройства
  
  // HTTP.on("/ssdp", handle_Set_Ssdp);         // Установить имя SSDP устройства по запросу вида /ssdp?ssdp=proba
  HTTP.on("/set_timmer", handle_setTimerFromRadio);            
  
  HTTP.on("/ssid", handle_Set_Ssid);            // Установить имя и пароль роутера по запросу вида /ssid?ssid=home2&password=12345678
  // HTTP.on("/ssidap", handle_Set_Ssidap);     // Установить имя и пароль для точки доступа по запросу вида /ssidap?ssidAP=home1&passwordAP=8765439
  
  HTTP.on("/restart", handle_Restart);          // Перезагрузка модуля по запросу вида /restart?device=ok
  // Запускаем HTTP сервер
  HTTP.begin();
}

void SSDP_init() {  // SSDP дескриптор
  Serial.print("Start SSDP ");
  HTTP.on("/description.xml", HTTP_GET, [](){
   SSDP.schema(HTTP.client());
  });
  //Если версия  2.0.0 закаментируйте следующую строчку
  SSDP.setDeviceType("upnp:rootdevice");
  SSDP.setSchemaURL("description.xml");
  SSDP.setHTTPPort(80);
  SSDP.setName(SSDP_Name);
  SSDP.setSerialNumber("001788102201");
  SSDP.setURL("/");
  SSDP.setModelName("xlooRoomClimatic");
  SSDP.setModelNumber("000000000001");
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

void handle_setTimerFromRadio(){
 setTimer = HTTP.arg("settimer");
 Serial.println("handle_setTimerFromRadio!");
 Serial.print(setTimer);
}
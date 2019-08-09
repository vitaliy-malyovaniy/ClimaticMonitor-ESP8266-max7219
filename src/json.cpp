#include <Arduino.h>
#include "json.h"

// DynamicJsonBuffer jsonBuffer;
// ------------- Чтение значения json
// сюда прилетает строка в виде JSON и имя из этого JSON объекта
String jsonRead(String &json, String name) {
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(json);
  return root[name].as<String>();
}

// ------------- Чтение значения json
int jsonReadtoInt(String &json, String name) {
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(json);
  return root[name];
}

// ------------- Запись значения json int
// сюда прилетает строка в виде JSON, имя из этого JSON объекта и значение для него
String jsonWrite(String &json, String name, float volume) {
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(json);
  root[name] = volume;
  json = "";
  root.printTo(json);
  return json;
}

// ------------- Запись значения json String
String jsonWrite(String &json, String name, String volume) {
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(json);
  root[name] = volume;
  json = "";
  root.printTo(json);
  return json;
}

/////////////////////////////////..................
// https://circuits4you.com/2019/01/11/nodemcu-esp8266-arduino-json-parsing-example/
// https://randomnerdtutorials.com/decoding-and-encoding-json-with-arduino-or-esp8266/
// https://techtutorialsx.com/2016/08/06/esp8266-parse-json-arrays/
// https://arduinojson.org/v6/api/jsonarray/createnestedarray/

// Перегрузка функций
// ------------- Создание данных для графика
String graf(int datas) {
  String root = "{}";  // Формировать строку для отправки в браузер json формат
  // {"data":[1]}
  // Резервируем память для json обекта буфер может рости по мере необходимти, предпочтительно для ESP8266
  DynamicJsonBuffer jsonBuffer;
  // вызовите парсер JSON через экземпляр jsonBuffer
  JsonObject& json = jsonBuffer.parseObject(root);
  // Заполняем поля json
  JsonArray& data = json.createNestedArray("data");
  data.add(datas);
  // Помещаем созданный json в переменную root
  root = "";
  json.printTo(root);
  return root;
}

// ------------- Создание данных для графика
String graf(float datas) {
  String root = "{}";  // Формировать строку для отправки в браузер json формат
  // {"data":[1]}
  // Резервируем память для json обекта буфер может рости по мере необходимти, предпочтительно для ESP8266
  DynamicJsonBuffer jsonBuffer;
  // вызовите парсер JSON через экземпляр jsonBuffer
  JsonObject& json = jsonBuffer.parseObject(root);
  // Заполняем поля json
  JsonArray& data = json.createNestedArray("data");
  data.add(datas);
  // Помещаем созданный json в переменную root
  root = "";
  json.printTo(root);
  return root;
}

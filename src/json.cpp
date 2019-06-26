#include <Arduino.h>
#include "json.h"

// ------------- Чтение значения json
// String jsonRead(String &json, String name) {
//   DynamicJsonBuffer jsonBuffer;
//   JsonObject& root = jsonBuffer.parseObject(json);
//   return root[name].as<String>();
// }

// ------------- Чтение значения json
// int jsonReadtoInt(String &json, String name) {
//   DynamicJsonBuffer jsonBuffer;
//   JsonObject& root = jsonBuffer.parseObject(json);
//   return root[name];
// }

// ------------- Запись значения json String
String jsonWrite(String &json, String name, String volume) {
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(json);
  root[name] = volume;
  json = "";
  root.printTo(json);
  return json;
}

// ------------- Запись значения json int
String jsonWrite(String &json, String name, float volume) {
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(json);
  root[name] = volume;
  json = "";
  root.printTo(json);
  return json;
}
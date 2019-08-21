#include <ArduinoJson.h>        //Установить из менеджера библиотек v5.8.1_ID64 !!!

String jsonRead(String &, String);
// int jsonRead(String &, String);

String jsonWrite(String &, String, String);
String jsonWrite(String &, String, float);

String graf(int);
String graf(float);
String graf(int16_t *, uint8_t);
String graf(int16_t *, float *, uint8_t);
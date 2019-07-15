#include "FileConfig.h"
#include "HTTPinit.h"
#include "WIFI.h"
#include "sensorsDHT11.h"


void saveConfig (){
  writeFile("config.json", configSetup );
}

  // ------------- Чтение файла в строку
  //  сюда прилетает имя JSON файла и максимальный для него размер
String readFile(String fileName, size_t len ) {  
  File configFile = SPIFFS.open("/" + fileName, "r");  // Открываем файл для чтения
  if (!configFile) {    // если файл не найден  
    return "Failed";
  }
  size_t size = configFile.size();
  if (size > len) {
    configFile.close();
    return "Large";
  }
  String temp = configFile.readString();
  configFile.close();
  return temp;
}

// ------------- Запись строки в файл
String writeFile(String fileName, String strings ) {
  File configFile = SPIFFS.open("/" + fileName, "w");
  if (!configFile) {
    return "Failed to open config file";
  }
  configFile.print(strings);
  //strings.printTo(configFile);
  configFile.close();
  return "Write sucsses";
}


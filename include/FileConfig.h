#pragma once
#include <Arduino.h>
#include <FS.h>

void saveConfig(void);  
String readFile(String, size_t);
String writeFile(String, String);
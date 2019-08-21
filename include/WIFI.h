#ifndef WIFI_H
#define WIFI_H 
#include <ESP8266WiFi.h>        //Содержится в пакете

// // Определяем переменные
extern String _ssid;     // Для хранения SSID
extern String _password; // Для хранения пароля сети
extern String _ssidAP;   // SSID AP точки доступа
extern String _passwordAP;   // пароль точки доступа
extern String SSDP_Name;

void WIFIinit(void);
bool StartAPMode(void);

#endif
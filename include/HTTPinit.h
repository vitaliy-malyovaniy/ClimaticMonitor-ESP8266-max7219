#ifndef HTTPINIT_H
#define HTTPINIT_H 
#include <Arduino.h>
#include <ESP8266WebServer.h>   //Содержится в пакете
#include <ESP8266SSDP.h>        // Видео с уроком http://esp8266-arduinoide.ru/step3-ssdp

extern String configJson;
extern String configSetup;
extern String sensorsJson;

void HTTP_init(void);
void SSDP_init (void);

void handle_Set_Ssdp(void);
void handle_Set_Ssid (void);
void handle_Restart(void);

#endif
#ifndef HTTPINIT_H
#define HTTPINIT_H 
#include <Arduino.h>
#include <ESP8266WebServer.h>   //Содержится в пакете
#include <ESP8266SSDP.h>        // Видео с уроком http://esp8266-arduinoide.ru/step3-ssdp
#include <ArduinoJson.h>

extern String configJson;
extern String sensorsJson;
extern String jsonConfig;
extern String setTimer;
extern int varTimer;

void HTTP_init(void);
void SSDP_init (void);
void handle_PC_On(void);

void handle_ConfigJSON(void);
void handle_Set_Ssdp(void);
void handle_Set_Ssid (void);
void handle_Set_Ssidap(void);
void handle_Restart(void);
void handle_setTimerFromRadio(void);

#endif
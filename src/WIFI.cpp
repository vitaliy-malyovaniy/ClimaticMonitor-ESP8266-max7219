#include "WIFI.h"


// // Определяем переменные
// String _ssid     = "Search-M";     // Для хранения SSID
// String _password = "RunTeaM36aLI"; // Для хранения пароля сети
String _ssid     = "WX3";
String _password = "wx123456";
String _ssidAP = "WiFi";   // SSID AP точки доступа
String _passwordAP = "";   // пароль точки доступа
IPAddress apIP(192, 168, 4, 1);
String SSDP_Name = "Climate monitor";

bool StartAPMode()
{ // Отключаем WIFI
  WiFi.disconnect();
  // Меняем режим на режим точки доступа
  WiFi.mode(WIFI_AP);
  // Задаем настройки сети
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  // Включаем WIFI в режиме точки доступа с именем и паролем
  // хронящихся в переменных _ssidAP _passwordAP
  WiFi.softAP(_ssidAP.c_str(), _passwordAP.c_str());
  return true;
}

void WIFIinit() {
  Serial.println("Start WIFIinit...");
  // Попытка подключения к точке доступа
  WiFi.mode(WIFI_STA);
  byte tries = 11;      // колличество попыток подключения
  WiFi.begin(_ssid.c_str(), _password.c_str());
  // Делаем проверку подключения до тех пор пока счетчик tries
  // не станет равен нулю или не получим подключение
  while (--tries && WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(1000);
  }
  if (WiFi.status() != WL_CONNECTED)  // Если не удалось подключиться запускаем в режиме AP
  {
    Serial.println("");
    Serial.println("WiFi up AP");
    StartAPMode();
  }
  else { // Иначе удалось подключиться отправляем сообщение
         // о подключении и выводим адрес IP
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  }
}
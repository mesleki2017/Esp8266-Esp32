#include <Arduino.h>
#ifdef ESP32
#include <WiFi.h>
#include <AsyncTCP.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>
#include <FS.h> 

extern "C" {
#include "user_interface.h"
}

AsyncWebServer server(80);

//Enter your SSID and PASSWORD
const char* ssid = "ESP8266";
const char* password = "12345678";





void setup(void){
  ESP.eraseConfig();//2019-12-19yeni
   Serial.begin(115200);
  SPIFFS.begin();
  if(SPIFFS.begin()){
     Serial.println("SPIFFS dosya sistemi aktif");
    //return;
  }

    File file1 = SPIFFS.open("/d3.v4.min.js", "r");
  if(file1){
    Serial.println("d3.v4.min.js acildi");
   
  }
      File file2 = SPIFFS.open("/index.html", "r");
  if(file2){
    Serial.println("index.html acildi");
  }
      File file3 = SPIFFS.open("/resim1.jpeg", "r");
  if(file2){
    Serial.println("resim1.jpeg acildi");
  }
   

   
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html");
  });
    server.on("/d3.v4.min.js", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/d3.v4.min.js", "application/javascript");
  });

     server.on("/resim1.jpeg", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/resim1.jpeg","image/jpeg");
  });

  
  server.begin();

  Serial.println("setupbitti");
}



  
void loop(){
 //server.serveStatic("/resim1.jpeg", SPIFFS, "/resim1.jpeg");
uint32_t free = system_get_free_heap_size();//yenibilgi2019-12-9 free rami gormek icin. genel kodla alakasi yok . test amacli.
Serial.println(free);
}

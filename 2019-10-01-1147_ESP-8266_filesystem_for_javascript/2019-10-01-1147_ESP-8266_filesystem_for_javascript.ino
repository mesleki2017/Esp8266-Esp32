
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <FS.h> 
ESP8266WebServer server(80); 
//Enter your SSID and PASSWORD
const char* ssid = "ESP8266";
const char* password = "12345678";

void setup(void){
  pinMode(2,OUTPUT);
  Serial.begin(115200);
  SPIFFS.begin();
  if(SPIFFS.begin()){
     Serial.println("SPIFFS dosya sistemi aktif");
    //return;
  }
    File file1 = SPIFFS.open("/d3.v4.js", "r");
  if(file1){
    Serial.println("file1 acildi");
   
  }
      File file2 = SPIFFS.open("/201910011147d3v2.html", "r");
  if(file2){
    Serial.println("file2 acildi");
   
  }

  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();

  server.serveStatic("/", SPIFFS, "/201910011147d3v2.html"); 
  server.serveStatic("/d3.v4.js", SPIFFS, "/d3.v4.js");
  server.begin();

}
//===============================================================
// This routine is executed when you open its IP in browser
//===============================================================
void loop(void){
  server.handleClient();  
}

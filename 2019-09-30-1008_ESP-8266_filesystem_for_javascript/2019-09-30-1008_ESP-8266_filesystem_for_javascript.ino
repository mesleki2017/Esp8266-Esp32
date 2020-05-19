

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <FS.h>
 
ESP8266WebServer server(80);
 
//Enter your SSID and PASSWORD
const char* ssid = "ESP8266";
const char* password = "12345678";

//===============================================================
// Setup
//===============================================================
 
void setup(void){
  pinMode(2,OUTPUT);
  Serial.begin(115200);
  SPIFFS.begin();

  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();

  server.serveStatic("/", SPIFFS, "/index.html"); 
  server.serveStatic("/d3.min.js", SPIFFS, "/d3.min.js");
  server.begin();


}
 
//===============================================================
// This routine is executed when you open its IP in browser
//===============================================================
void loop(void){

  
  server.handleClient();


  
}


#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <FS.h> 

ESP8266WebServer server(80); 
//Enter your SSID and PASSWORD
const char* ssid = "ESP8266";
const char* password = "12345678";

int m=1;

void handleLED() { 
  String aa = server.arg("xxx"); //Refer  xhttp.open("GET", "setLED?xxx="+today.getTime(), true)

String str1="";

if (m==0)str1="javascritin calistirildigi sistemden ESP ye zaman alinmadi";
if (m==1)str1="javascritin calistirildigi sistemden ESP ye zaman alindi";


server.send(200, "text/plane",str1 ); //Send web page
//http://192.168.4.1/setLED sayfasina str1 gonderir


}

void setup(void){

  Serial.begin(115200);
  SPIFFS.begin();
  if(SPIFFS.begin()){
     Serial.println("SPIFFS dosya sistemi aktif");
    //return;
  }
  

      File file2 = SPIFFS.open("/index.html", "r");
  if(file2){
    Serial.println("file2 acildi");
   
  }

   
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  
  server.serveStatic("/", SPIFFS, "/index.html"); 
  server.begin();
  server.on("/setLED", handleLED);
  Serial.println("setupbitti");
  
}

void loop(void){
 server.handleClient(); 
}

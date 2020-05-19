
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <FS.h> 
#include <OneWire.h>
#include <DallasTemperature.h>
#include <ArduinoJson.h>

 unsigned long zaman1=0;
 unsigned long k=1;

ESP8266WebServer server(80); 
//Enter your SSID and PASSWORD
const char* ssid = "ESP8266";
const char* password = "12345678";



void setup(void){
 
  Serial.begin(115200);
  SPIFFS.begin();
  if(SPIFFS.begin()){
     Serial.println("SPIFFS dosya sistemi aktif");
    //return;
  }
  File file5 = SPIFFS.open("/data5.json", "w");
    if(file5){
    Serial.println("data5.json acildi");
    }
    else
    {Serial.println("data5.json ACILMADI");}
  
  
  StaticJsonDocument<200> doc;
  JsonArray zaman00 = doc.createNestedArray("zaman");
  JsonArray analog00 = doc.createNestedArray("analog");
//  JsonArray data = doc.createNestedArray("data");
//  data.add(48.756080);
//  data.add(2.302038);
  zaman00.add(0);
  analog00.add(30);
  zaman00.add(1);
  analog00.add(15);
  serializeJson(doc, Serial);serializeJson(doc, file5);
  Serial.println();




  
  
  pinMode(2,OUTPUT);
  
  SPIFFS.begin();
  if(SPIFFS.begin()){
     Serial.println("SPIFFS dosya sistemi aktif");
    //return;
  }
    File file1 = SPIFFS.open("/d3.min.js", "r");
  if(file1){
    Serial.println("file1 acildi");
   
  }
      File file2 = SPIFFS.open("/2019-10-02-1316.html", "r");
  if(file2){
    Serial.println("file2 acildi");
   
  }
   
      File file3 = SPIFFS.open("/data5.json", "r");
  if(file3){
    Serial.println("data5 acildi99999");
   
  }
   
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();

  server.serveStatic("/", SPIFFS, "/2019-10-02-1316.html"); 
  server.serveStatic("/d3.min.js", SPIFFS, "/d3.min.js");
  server.serveStatic("/data5.json", SPIFFS, "/data5.json");
  server.begin();

}

void dataekle(){
  unsigned long zaman2 = millis();
  if ( zaman2 - zaman1 > 5000 ) {
    zaman1=zaman2;
    k=k*(k+1);
    Serial.print("zaman1/1000=");Serial.print(zaman1/1000);Serial.print("---k=");Serial.print(k);
  }
  
}



void loop(void){
  server.handleClient(); 
  dataekle();


}

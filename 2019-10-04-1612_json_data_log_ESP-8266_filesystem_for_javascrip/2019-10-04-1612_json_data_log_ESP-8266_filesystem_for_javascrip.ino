
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
  StaticJsonDocument<200> doc;
  JsonArray zaman00 = doc.createNestedArray("zaman");
  JsonArray analog00 = doc.createNestedArray("analog");

void dataekle(){
  unsigned long zaman2 = millis();
  if ( zaman2 - zaman1 > 5000 ) {
    zaman1=zaman2;
    k=(k+1);
  Serial.print("zaman1/1000=");Serial.print(zaman1/1000);Serial.print("---k=");Serial.println(k);
  
  File file5 = SPIFFS.open("/data5.json", "w");
    if(!file5){
    Serial.println("data5.json ACILMADI");
    }

  if ( file5.size() < 440 ) {
  zaman00.add(zaman1/1000);
  analog00.add(k);
  serializeJson(doc, Serial);serializeJson(doc, file5);
 Serial.print("file.size()===="); Serial.println(file5.size());
  }
  else{
   zaman00.remove(0);
    analog00.remove(0);
    serializeJson(doc, Serial);serializeJson(doc, file5);
  }
  
  }
  
}



void loop(void){
  server.handleClient(); 
 dataekle();


}

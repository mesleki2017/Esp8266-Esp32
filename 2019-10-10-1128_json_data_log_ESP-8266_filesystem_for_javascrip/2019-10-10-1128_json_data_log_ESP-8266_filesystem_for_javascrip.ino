
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <FS.h> 
#include <ArduinoJson.h>

 unsigned long zaman1=0;
 unsigned long k=0;

ESP8266WebServer server(80); 
//Enter your SSID and PASSWORD
const char* ssid = "ESP8266";
const char* password = "12345678";

DynamicJsonDocument doc(840);
JsonArray x = doc.createNestedArray("x");
JsonArray y = doc.createNestedArray("y");
//char docbuf[400];

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
   
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();

  server.serveStatic("/", SPIFFS, "/2019-10-02-1316.html"); 
  server.serveStatic("/d3.min.js", SPIFFS, "/d3.min.js");
  server.serveStatic("/data5.json", SPIFFS, "/data5.json");
  server.begin();

}

void dataekle(){
  unsigned long zaman2 = millis();
  if ( zaman2 - zaman1 > 1000 ) {
    zaman1=zaman2;
    k=(k+1);
 Serial.print("zaman1/1000=");Serial.print(zaman1/1000);Serial.print("---k=");Serial.println(k);
  
  File file5 = SPIFFS.open("/data5.json", "w");
    if(!file5){
    Serial.println("data5.json ACILMADI");
    }

  //if ( doc.memoryUsage() < 400 ) {
  //if ( int(file5.size()) < 50 ) {

  ////////////////////////////////////////////////////////////////////////////////
  if ( x.size() < 5 ) {
  x.add(zaman1/1000);
  y.add(k);
 // analog00.add(k);
 serializeJson(doc, file5);//doc json alanini file5 e yani data6.json dosyasina a yazar
 serializeJson(doc, Serial); Serial.println("");//doc json alanini Seri port ekranina yazar ve alt satira gecer
 Serial.print("file.size()===="); Serial.println(int(file5.size()));
 Serial.print("doc.memoryUsage())===="); Serial.println(doc.memoryUsage());
 Serial.print("zaman00.size()===="); Serial.println(x.size());
 
 //file5.close();
  }
  else{
   Serial.println("JSON DOSYA doldu");
   x.remove(0);
   y.remove(0);
   x[k+1]=555;
//   zaman00.add(zaman1/1000);
//   analog00.add(k);
   serializeJson(doc, file5);
   serializeJson(doc, Serial); Serial.println("");
   Serial.print("file.size()===="); Serial.println(int(file5.size()));
   Serial.print("doc.memoryUsage())===="); Serial.println(doc.memoryUsage());
   Serial.print("zaman00.size()===="); Serial.println(x.size());
   
   
   //file5.close();
  }
  //////////////////////////////////////////////////////////////////////////////////////
//if ( doc.memoryUsage() < 400 ) {
//Serial.println("doc.clear();===="); doc.clear();
//Serial.println("doc.memoryUsage()====doc.clear();"); Serial.println(doc.memoryUsage());
//  
//}



  /////////////////////////////////////////////////////////////
  }
  
}



void loop(void){
  server.handleClient(); 
 dataekle();


}

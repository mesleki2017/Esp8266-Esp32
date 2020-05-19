
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <FS.h> 
#include <ArduinoJson.h>

#define ONE_WIRE_BUS 5                          //D1 pin of nodemcu
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);            // Pass the oneWire reference to Dallas Temperature.


 unsigned long zaman1=0;
 unsigned long k=0;

ESP8266WebServer server(80); 
//Enter your SSID and PASSWORD
const char* ssid = "ESP8266";
const char* password = "12345678";

DynamicJsonDocument doc(1680);
JsonArray x = doc.createNestedArray("x");
JsonArray y = doc.createNestedArray("y");


void setup(void){
  sensors.begin();
 
  Serial.begin(115200);
  SPIFFS.begin();
  if(SPIFFS.begin()){
     Serial.println("SPIFFS dosya sistemi aktif");
    //return;
  }
  
    File file1 = SPIFFS.open("/d3.v4.min.js", "r");
  if(file1){
    Serial.println("file1 acildi");
   
  }
      File file2 = SPIFFS.open("/index.html", "r");
  if(file2){
    Serial.println("file2 acildi");
   
  }
   
      File file3 = SPIFFS.open("/data5.json", "r");
  if(file3){
    Serial.println("data5 acildi99999");
   
  }
   
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();

  server.serveStatic("/", SPIFFS, "/index.html"); 
  server.serveStatic("/d3.v4.min.js", SPIFFS, "/d3.v4.min.js");
  server.serveStatic("/data5.json", SPIFFS, "/data5.json");
  server.begin();

}

void dataekle(){
  unsigned long zaman2 = millis();
  if ( zaman2 - zaman1 > 1000 ) {
    sensors.requestTemperatures();
    float a = sensors.getTempCByIndex(0);
    zaman1=zaman2;
  
  File file5 = SPIFFS.open("/data5.json", "w");
    if(!file5){
    Serial.println("data5.json ACILMADI");
    }



  ////////////////////////////////////////////////////////////////////////////////
  if ( x.size() < 50 ) {
  x.add(zaman1/1000);
  y.add(a);
  //doc["x"][k]=k;
 serializeJson(doc, file5);//doc json alanini file5 e yani data6.json dosyasina a yazar
 serializeJson(doc, Serial); Serial.println("");//doc json alanini Seri port ekranina yazar ve alt satira gecer
 
 //file5.close();
  }
  else{
    
    
    doc["x"][49-k]=49-k;
    doc["y"][49-k]=a;
    serializeJson(doc, file5);
    serializeJson(doc, Serial); Serial.println("");//doc json alanini Seri port ekranina yazar ve alt satira gecer
    k=(k+1);
    if ( k>=50){k=0;}
    Serial.print(k);Serial.println("*******");
    }
  
  
  }
  
}



void loop(void){
  server.handleClient(); 
 dataekle();


}

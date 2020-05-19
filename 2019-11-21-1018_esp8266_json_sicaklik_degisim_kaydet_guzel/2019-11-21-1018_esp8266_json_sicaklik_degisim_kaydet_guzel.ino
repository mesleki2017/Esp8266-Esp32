
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <FS.h> 
#include <ArduinoJson.h>
#include <TimeLib.h>

#define ONE_WIRE_BUS 5                          //D1 pin of nodemcu
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);            // Pass the oneWire reference to Dallas Temperature.


time_t t1=0;
time_t t2=0;
time_t t3=0;
float a1;
float a2;
int n=0;

ESP8266WebServer server(80); 
//Enter your SSID and PASSWORD
const char* ssid = "ESP8266";
const char* password = "12345678";

DynamicJsonDocument doc(1680);
JsonArray x = doc.createNestedArray("x");
JsonArray y = doc.createNestedArray("y");

void setup(void){
  setTime(0,00,00,1,01,2019);
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
  time_t t1 = now();
  t3=t1;
  sensors.requestTemperatures();
  a1 = sensors.getTempCByIndex(0);
}

void zamandongu()
{
  t2 = now();

  if ( (t2 - t1)>= 1 ) {
    t1=t2;
    sensors.requestTemperatures();
    a2 = sensors.getTempCByIndex(0);  
    Serial.print("a2-a1 =>");Serial.println(a2-a1);
    if ( (a2*100-a1*100)>=100 || (a2*100-a1*100)<=-100 || n==0 ){Serial.println("denemeeee");dataekle1();a1=a2;n=n+1; }// sicaklik degisimi 1 dereceden fazla is json a data ekle
    // a2 ve a1 100 ile carpmam floating islemlerde sikinti oldugunu okudum internette
    
  }  
}
void dataekle1()
{
 File file5 = SPIFFS.open("/data5.json", "w");
 if(!file5){Serial.println("data5.json ACILMADI");}

if ( x.size() < 50 )
    {
    x.add(t2-t3);
    y.add(a2);
    //doc["x"][k]=k;
    serializeJson(doc, file5);//doc json alanini file5 e yani data5.json dosyasina a yazar 
    }
    else
    {
    serializeJson(doc, file5);// x.size 50 den buyuk olunca chrome da json dsoyasi alinamiyordu. bu sekilde ekleyince duzeldi??
    }
               
}
  
void loop(void){
 server.handleClient(); 
 zamandongu();
}

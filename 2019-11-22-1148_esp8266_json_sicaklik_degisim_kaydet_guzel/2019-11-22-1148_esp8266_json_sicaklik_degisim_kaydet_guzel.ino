
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
time_t t4=0;
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

void handleLED() {
 String aa = server.arg("xxx"); //Refer  xhttp.open("GET", "setLED?LEDstate="+led, true);
  aa.remove(10);//javascripten gelen time 13 haneli milisecond da iceriyor. arduino daki time 10 haneli milsecond icermiyor
  int bb=aa.toInt();//string i int e cevirme
 t4=bb;// t4 bir time_t degiskeni en ustte taninli
 Serial.print("bb =>");Serial.println(bb);
 server.send(200, "text/plane", "gjhgjhg"); //Send web page
 setTime(t4);// javascriten gelen time arduino sistem time yapma
 time_t t1 = now();
 Serial.print("**** =>");Serial.println(t1);
 t3=t1;//t3 artik kullanmiyorum
}

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
   
      File file5 = SPIFFS.open("/data5.json", "w");///deneme
  if(file5){
    Serial.println("data5 acildi99999");
  }
   
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();

  server.serveStatic("/", SPIFFS, "/index.html"); 
  server.serveStatic("/d3.v4.min.js", SPIFFS, "/d3.v4.min.js");
  server.serveStatic("/data5.json", SPIFFS, "/data5.json");
  server.begin();
  server.on("/setLED", handleLED);
  time_t t1 = now();
  t3=t1;
  sensors.requestTemperatures();
  a1 = sensors.getTempCByIndex(0);
//  x.add(0);///deneme 0 0 eklemek ise yaramadi
//  y.add(0);///deneme
//  serializeJson(doc, file5);///deneme
}

void zamandongu()
{
  File file5 = SPIFFS.open("/data5.json", "w");///deneme
  serializeJson(doc, file5);///deneme bu iki satirin faydasi varmi ?
  
  
  t2 = now();

  if ( (t2 - t1)>= 1 ) {
    Serial.println("qqqqq");
    t1=t2;
    sensors.requestTemperatures();
    a2 = sensors.getTempCByIndex(0);  
    if ( (a2*100-a1*100)>=100 || (a2*100-a1*100)<=-100 || n==0 ){Serial.println("denemeeee");dataekle1();a1=a2;n=n+1; }// sicaklik degisimi 1 dereceden fazla is json a data ekle
    // a2 ve a1 100 ile carpmam floating islemlerde sikinti oldugunu okudum internette
    
  }  
}
void dataekle1()
{
 File file5 = SPIFFS.open("/data5.json", "w");//deneme
 if(!file5){Serial.println("data5.json ACILMADI");}//deneme
if ( t4 !=0 ){//t4 yani javascipten time gelmisse 0 dan farki olur ve calisir
  t2 = now();
if ( x.size() < 50 )
    {
    x.add(t2);
    y.add(a2);
    //doc["x"][k]=k;
    serializeJson(doc, file5);//doc json alanini file5 e yani data5.json dosyasina a yazar 
    }
    else
    {
    serializeJson(doc, file5);// x.size 50 den buyuk olunca chrome da json dsoyasi alinamiyordu. bu sekilde ekleyince duzeldi??
    }
}               
}
  
void loop(void){
 server.handleClient(); 
 zamandongu();
}

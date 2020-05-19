
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
time_t t4=0;
float a1;
float a2;
int n=0;
int m=0;
File file5;//file5 birden fazla yerde oldugu icin global
String aa;// aa yi daha once local yapmistim handleLED in icindei her fonksiyon tetiklendiginde O landi
ESP8266WebServer server(80); 
//Enter your SSID and PASSWORD
const char* ssid = "ESP8266";
const char* password = "12345678";

DynamicJsonDocument doc(1680);
JsonArray x = doc.createNestedArray("x");
JsonArray y = doc.createNestedArray("y");

void handleLED() {
 
 if (m == 0 ){// javascripten sistem zamaninin bir kere alinmasi icin
 aa = server.arg("xxx"); //Refer  xhttp.open("GET", "setLED?xxx="+today.getTime(), true)
  Serial.print("aa=> ");Serial.println(aa);
 aa.remove(10);//javascripten gelen time 13 haneli milisecond da iceriyor. arduino daki time 10 haneli milsecond icermiyor
 int bb=aa.toInt();//string i int e cevirme
 if (bb == 0 ){Serial.println("zaman alinmadi daha");} else{m=m+1;Serial.print("m = ");Serial.println(m);Serial.print("bb = ");Serial.println(bb);}
 t4=bb;// t4 bir time_t degiskeni en ustte taninli
 //Serial.print("bb =>");Serial.println(bb);
 
 setTime(t4);// javascriten gelen time arduino sistem time yapma
 time_t t1 = now();
 }
server.send(200, "text/plane",String(m)); //Send web page
 //Serial.print("**** =>");Serial.println(t1);


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
   
  file5 = SPIFFS.open("/data5.json", "w");///deneme
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
  sensors.requestTemperatures();
  a1 = sensors.getTempCByIndex(0);

}

void zamandongu()
{

  t2 = now();
  Serial.println(t2-t1);
  if ( (t2 - t1)>= 1 ) {
    t1=t2;
    sensors.requestTemperatures();
    a2 = sensors.getTempCByIndex(0);  
    if ( (a2*100-a1*100)>=10 || (a2*100-a1*100)<=-10 || n==0 ){Serial.println("yeni sicaklik eklenecek");dataekle1();a1=a2;n=n+1; }// sicaklik degisimi 1 dereceden fazla is json a data ekle
    // a2 ve a1 100 ile carpmam floating islemlerde sikinti oldugunu okudum internette
    
  }  
}
void dataekle1()
{
 File file5 = SPIFFS.open("/data5.json", "w");//deneme
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

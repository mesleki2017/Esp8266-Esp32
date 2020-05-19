
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
int k=0;
File file5;
File file6;
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

String str1="";

if (m==0)str1="javascritin calistirildigi sistemden ESP ye zaman alinmadi";
if (m==1)str1="javascritin calistirildigi sistemden ESP ye zaman alindi";


server.send(200, "text/plane",str1 ); //Send web page
//http://192.168.4.1/setLED sayfasina str1 gonderir


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
      file6 = SPIFFS.open("/data6.json", "a+");///deneme
  if(file5){
    Serial.println("data6 acildi99999");
  }
   
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  
  server.serveStatic("/", SPIFFS, "/index.html"); 
  server.serveStatic("/d3.v4.min.js", SPIFFS, "/d3.v4.min.js");
  server.serveStatic("/data5.json", SPIFFS, "/data5.json");
  server.serveStatic("/data6.json", SPIFFS, "/data6.json");
  server.begin();
  server.on("/setLED", handleLED);
  setTime(1000);
  time_t t1 = now();
  time_t t4 = now();
  sensors.requestTemperatures();
  a1 = sensors.getTempCByIndex(0);
//  x.add(0);
//  y.add(0);
//  serializeJson(doc, file5);
//  delay(1000);
  Serial.println("setupbitti");
}

void zamandongu()
{
  t2 = now();  
  if ( (t2 - t1)>= 1 ) {
    //Serial.print("t2=> ");Serial.println(t2);
    t1=t2;
    sensors.requestTemperatures();
    a2 = sensors.getTempCByIndex(0);  
    if ( (a2*100-a1*100)>=10 || (a2*100-a1*100)<=-10 || n==0 ){Serial.println("yeni sicaklik eklenecek");dataekle1();a1=a2;n=n+1; }// sicaklik degisimi 1 dereceden fazla is json a data ekle
    // a2 ve a1 100 ile carpmam floating islemlerde sikinti oldugunu okudum internette
    
  }  
}
void dataekle1()
{
file5 = SPIFFS.open("/data5.json", "w");//sanirim her actiginda bos data5.json dsoyasi aciyor

if ( t2 >= 1000||n==1){//t4 yani javascipten time gelmisse 0 dan farki olur ve calisir
  t2 = now();
if ( x.size() < 4 )
    {
    x.add(t2);
    y.add(a2);
    Serial.print("n=> ");Serial.print(n);Serial.print(", t2=> ");Serial.print(t2);Serial.print(", a2=> ");Serial.println(a2);
    serializeJson(doc, file5);//doc json alanini file5 e yani data5.json dosyasina a yazar 
    Serial.print("filesize=> ");Serial.println(file5.size());
    }
    else
    {
    serializeJson(doc, file5);// x.size 50 den buyuk olunca chrome da json dsoyasi alinamiyordu. bu sekilde ekleyince duzeldi??
    Serial.print("filesize5=> ");Serial.println(file5.size());
    
    //if ( k==0 && file6.size()<=1000){
    if ( k==0 ){
    file6 = SPIFFS.open("/data6.json", "a+");//2019-11-28-0930 yenibilgi: "a+","w+"
    serializeJson(doc, file6);
    //Serial.print("filesize5=> ");Serial.println(file6.size());
    file6.close();
    k=k+1;
    file6duzelt();
    }
    Serial.print("kayit SONA ERDI");
    }
}               
}

void file6duzelt(){
  file6 = SPIFFS.open("/data6.json", "r+");// r+ ise yaradi digerleri olmadi
  if(file6){Serial.print("filesize6=> ");Serial.println(file6.size());}
while(file6.available()){
  String line=file6.readStringUntil('}');
  Serial.println(line);
  n=file6.position();
  Serial.print("n=>");Serial.println(n);
  file6.print(",");
  }
  file6.seek(0);
  file6.print("[");//oldu
  file6.seek(SeekEnd);//olmadi bu
  file6.print("]");
  file6.close();
  
}


  
void loop(void){
 server.handleClient(); 
 zamandongu();
}

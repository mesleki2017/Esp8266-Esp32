
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


time_t donguZamanDegiskeni=0;
time_t suAndakiZaman=0;
time_t espyeAlinanZaman=0;
float oncekiSicaklik;
float sicaklik;
int n=0;
int m=0;
int k=0;
File file5;//anlik kayit
File file6;//gecmis kayit
String javascriptenZamanTxt;// javascriptenZamanTxt i daha once local yapmistim espyeZamanAl in icindei her fonksiyon tetiklendiginde O landi
ESP8266WebServer server(80); 
//Enter your SSID and PASSWORD
const char* ssid = "ESP8266";
const char* password = "12345678";

DynamicJsonDocument doc(3400);
JsonArray x = doc.createNestedArray("x");
JsonArray y = doc.createNestedArray("y");

void espyeZamanAl() {
 
 if (m == 0 ){// javascripten sistem zamaninin sadece bir kere alinmasi icin
 javascriptenZamanTxt = server.arg("chromedanzamanbilgisi"); //Refer  xhttp.open("GET", "setLED?xxx="+today.getTime(), true)
  Serial.print("javascriptenZamanTxt=> ");Serial.println(javascriptenZamanTxt);
 javascriptenZamanTxt.remove(10);//javascripten gelen time 13 haneli milisecond da iceriyor. arduino daki time 10 haneli second formatinda
 int alinanZamanSaniye=javascriptenZamanTxt.toInt();//string i int e cevirme
 if (alinanZamanSaniye == 0 ){Serial.println("zaman alinmadi daha");} else{m=m+1;}
 espyeAlinanZaman=alinanZamanSaniye;// espyeAlinanZaman bir time_t degiskeni olarak en ustte tanimli
 //Serial.print("bb =>");Serial.println(bb);
 
 setTime(espyeAlinanZaman);// javascriten gelen time arduino sistem time yapma
 time_t donguZamanDegiskeni = now();
 }

String str1="";

if (m==0)str1="javascritin calistirildigi sistemden ESP ye zaman alinmadi";
if (m==1)str1="javascritin calistirildigi sistemden ESP ye zaman alindi";


server.send(200, "text/plane",str1 ); //Send web page
//http://192.168.4.1/zamanAl sayfasina str1 yazar


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
    Serial.println("d3.v4.min.js acildi");
   
  }
      File file2 = SPIFFS.open("/index.html", "r");
  if(file2){
    Serial.println("index.html acildi");
   
  }
   File file22 = SPIFFS.open("/index2.html", "r");// data6 la ilgi websayfasi
  if(file22){
    Serial.println("index2 acildi");
   
  }
   
    file5 = SPIFFS.open("/data5.json", "w");//
  if(file5){
    Serial.println("data5.json acildi");
  }
      file6 = SPIFFS.open("/data6.json", "a+");//
  if(file5){
    Serial.println("data6.json acildi");
  }
   
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  
  server.serveStatic("/", SPIFFS, "/index.html"); 
  server.serveStatic("/d3.v4.min.js", SPIFFS, "/d3.v4.min.js");
  server.serveStatic("/data5.json", SPIFFS, "/data5.json");
  server.serveStatic("/data6.json", SPIFFS, "/data6.json");
  server.serveStatic("/index2.html", SPIFFS, "/index2.html");
  server.begin();
  server.on("/zamanAl", espyeZamanAl);
  setTime(1000);
  time_t donguZamanDegiskeni = now();
  time_t espyeAlinanZaman = now();
  sensors.requestTemperatures();
  oncekiSicaklik = sensors.getTempCByIndex(0);
//  x.add(0);
//  y.add(0);
//  serializeJson(doc, file5);
//  delay(1000);
  Serial.println("setupbitti");
}

void zamandongu()// 1 sn de bir sicaklik olcer
{
  suAndakiZaman = now();  
  if ( (suAndakiZaman - donguZamanDegiskeni)>= 1 ) {
    donguZamanDegiskeni=suAndakiZaman;
    sensors.requestTemperatures();
    sicaklik = sensors.getTempCByIndex(0);  
    if (n==0){Serial.print("n====0====>");Serial.println(n);dataekle1();}
    if ( (sicaklik*100-oncekiSicaklik*100)>=10 || (sicaklik*100-oncekiSicaklik*100)<=-10  ){Serial.println("yeni sicaklik eklenecek");dataekle1();oncekiSicaklik=sicaklik; }// sicaklik degisimi 1 dereceden fazla is json a data ekle
    // sicaklik ve oncekiSicaklik 100 ile carpmam,n sebebi: floating islemlerde sikinti oldugunu okudum internette ve float tu 100 le carparak int islem yaptim
    
  }  
}
void dataekle1()
{
n=n+1;
file5 = SPIFFS.open("/data5.json", "w");//"w" ile  her actiginda bos data5.json dsoyasi aciyor
Serial.print("n===1=====>");Serial.println(n);
if ( suAndakiZaman >= 1570000000||n==1){//javascripten esp ye zaman bilgisi kayit basla butonuna basildiginda geliyor. ondan once suAndakiZaman 1000 den basliyor 
  //cunku setTime(1000) yaptim yukarida. 1000 de 1970 lere denk geliyor.suanki zaman milisanyei olarak 1575320042 civarinda k
  // n=01 de json dosyasinda ilk kayit olsun diye bir kayit aliyorum tarih yanlisda olsa . daha sonra ancak javascripten tarih bilgisi
  //gelirse kayit etmeye deam ediyor 
suAndakiZaman = now();
Serial.print("suAndakiZaman=>");Serial.println(suAndakiZaman);
if ( x.size() < 10 )//
    {
    x.add(suAndakiZaman);
    y.add(sicaklik);
    Serial.print("n=> ");Serial.print(n);Serial.print(", suAndakiZaman=> ");Serial.print(suAndakiZaman);Serial.print(", sicaklik=> ");Serial.println(sicaklik);
    serializeJson(doc, file5);//doc json alanini file5 e yani data5.json dosyasina a yazar 
    Serial.print("filesize=> ");Serial.println(file5.size());
    }
    else
    {
    serializeJson(doc, file5);// x.size 50 den buyuk olunca chrome da json dsoyasi alinamiyordu. bu sekilde ekleyince duzeldi??
    Serial.print("filesize5=> ");Serial.println(file5.size());
    
    //if ( k==0 && file6.size()<=1000){
    if ( k==0 && file6.size()<=50000 ){
     data6yaekle();
    k=k+1;
    }
    Serial.print("kayit SONA ERDI");
    doc.clear();
    JsonArray x = doc.createNestedArray("x");
    JsonArray y = doc.createNestedArray("y");
    k=0;
    }
}               
}
// ekle ve degistir sonun calisabilnesi icin data6.json ilk hali [{}] seklinde olmalisi lazımdi simdi [{}.bunun icin ne degisti bilmiyorum
void data6yaekle(){
  degistirSON(',');
  file6 = SPIFFS.open("/data6.json","a+");///deneme
  if(file6){
    Serial.println("data6 acildi99999");
  }
serializeJson(doc, file6);
file6.print("]");
file6.close();
}
void degistirSON(char b){
file6 = SPIFFS.open("/data6.json","r+");///deneme
while(file6.available()){
  int m=file6.size();
  file6.seek(m-1);
  file6.print(b);
  }
  file6.close();
}

  
void loop(void){
 server.handleClient(); 
 zamandongu();
}

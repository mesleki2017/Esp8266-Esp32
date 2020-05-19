#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
#define ARDUINOJSON_USE_DOUBLE 1
#include <ArduinoJson.h>
#include <TimeLib.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
//#include <Fonts/FreeSerif9pt7b.h>


#define TFT_CS D0  //for D1 mini or TFT I2C Connector Shield (V1.1.0 or later)
#define TFT_DC D8  //for D1 mini or TFT I2C Connector Shield (V1.1.0 or later)
#define TFT_RST -1 //for D1 mini or TFT I2C Connector Shield (V1.1.0 or later)
#define TS_CS D3   //for D1 mini or TFT I2C Connector Shield (V1.1.0 or later)

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
////////////////////////////////////////
int n=0;// 1 kere kontrolu icin
int i = -600;// kayan altyazi icin
///////////////////////////////
const char* ssid = "GM 9 Pro";
const char* password = "asdf12345678";
/////////////////////////////////////////
DynamicJsonDocument doc(16000);
DynamicJsonDocument doc1(5200);
/////////////////////////////////////////
time_t t2=0;
time_t t3=0;
/////////////////////////////////////////
char *ay[]={"","Ocak ","Subat","Mart ","Nisan","Mayis","Hazrn","Temmz","Agsts","Eylul","Ekim ","Kasim","Aralk"};
//char* gun[]={"","Pzar","Pzrt","Sali","Crsm","Prsm","Cuma","Cmrt"};
//char* gun[]={"","Pazar","Pazartesi","Sali","Carsamba","Persembe","Cuma","Cumartesi"};
/////////////////////////////////////////
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);
/////////////////////////////////////////
void setup()
{
  Serial.begin(115200);
  timeClient.begin();
  Serial.println("ILI9341 Test!");
  tft.begin();
  tft.setRotation(1);
  //tft.setFont(&FreeSerif9pt7b);
  tft.setTextWrap(false);//yenibilgi2019-12-11:
  tft.setTextColor(0x0000,0xffff); tft.setTextSize(2);
  tft.fillRect(0,0, 320,120, 0xffff);
  tft.fillRect(0,120,320,240,0xffff );
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
Serial.print("Connecting..");
tft.setCursor(10, 10);tft.print("baglaniyor");
delay(1000);
}
tft.setCursor(10, 10);tft.println("baglandi..");
delay(1000);

}
// datazaman ve datazaman1 bibirinin opsiyonu
int datazaman(int i){//yeni bilgi int tipi fonksiyon da return asagidaki gibi olabiliyor
  char zamantext[15];
  serializeJson(doc["list"][i]["dt_txt"], zamantext);//datazaman json dan zamanı butun text olarak aliyor
  tft.setTextColor(0x6043,0x6d56);
  return tft.print(zamantext);
 }
 
int datazaman1(int i){//yeni bilgi int tipi fonksiyon da return asagidaki gibi olabiliyor
  String zaman;
  time_t t1=0;
  String text1="";
  serializeJson(doc["list"][i]["dt"], zaman);//datazaman1 json dan zamanı saniye formatinda aliyor
  t1=zaman.toInt();
  tft.setTextColor(0x6043,0x6d56);
  text1=String(day(t1))+ String("-")+ay[month(t1)]+ String(" ");
  if (hour(t1) < 10)text1=text1+String("0");
  text1=text1+String(hour(t1))+ String(":");
  return tft.print(text1);
 }
 
int datasicaklik(int i){//yenibilgi int tipi fonksiyon da return asagidaki gibi olabiliyor
  String b="";
  String c="";
  String d="";
  serializeJson(doc["list"][i]["main"]["temp"], b);
  serializeJson(doc["list"][i]["weather"][0]["main"], c);
  int sicaklik=b.toInt();
  int renkq;
  if (   8>sicaklik && 0 <sicaklik){renkq=0xdec3;}
  if (   0>=sicaklik && -2 <sicaklik){renkq=0x6c56;}
  if (  -2>=sicaklik && -4 <sicaklik){renkq=0x6cf6;}
  if (  -4>=sicaklik && -6 <sicaklik){renkq=0x6d56;;}
  c.replace("\"","");//yenibilgi2019-12 : https://stackoverflow.com/questions/32414079/android-how-to-remove-character-from-string
  tft.setTextColor(0x6043,renkq);
  d= String(sicaklik)+" "+c;
  return tft.print(d);
 }
//yenibilgi https://chrishewett.com/blog/true-rgb565-colour-picker/

 int altin(String a)
 {
 String text2="";
 serializeJson(doc1["rates"][a], text2);
 float v=text2.toFloat();
 float z=1/v;
 //if (z <1473){uyari();}
 return tft.print(1/v); 
 }
 int dolar()
 {
  String text2="";
  serializeJson(doc1["rates"]["TRY"], text2);
  float v=text2.toFloat();
  return tft.print(v);
 }

int havatft2(int satiraralik){
  if(n==0){//ekrana 1 kere yazdirilsin 
tft.setTextSize(2);//yenibilgi https://forum.arduino.cc/index.php?topic=364055.0
tft.setCursor(0,0);tft.setTextColor(0xf2d0,0x84f0);tft.print(" Tarih  Saat C Hava ");
tft.setCursor(0,satiraralik*1);datazaman1(2);tft.setTextColor(0x6043,0xffff);tft.print(" ");datasicaklik(2);
tft.setCursor(0,satiraralik*2);datazaman1(3);tft.setTextColor(0x6043,0xffff);tft.print(" ");datasicaklik(3);
tft.setCursor(0,satiraralik*3);datazaman1(4);tft.setTextColor(0x6043,0xffff);tft.print(" ");datasicaklik(4);
tft.setCursor(0,satiraralik*4);datazaman1(5);tft.setTextColor(0x6043,0xffff);tft.print(" ");datasicaklik(5);
tft.setCursor(0,satiraralik*5);datazaman1(6);tft.setTextColor(0x6043,0xffff);tft.print(" ");datasicaklik(6);
tft.setCursor(0,satiraralik*6);datazaman1(7);tft.setTextColor(0x6043,0xffff);tft.print(" ");datasicaklik(7);
tft.setCursor(0,satiraralik*7);datazaman1(8);tft.setTextColor(0x6043,0xffff);tft.print(" ");datasicaklik(8);
tft.setCursor(0,satiraralik*8);datazaman1(9);tft.setTextColor(0x6043,0xffff);tft.print(" ");datasicaklik(9);
tft.setCursor(0,satiraralik*9);datazaman1(10);tft.setTextColor(0x6043,0xffff);tft.print(" ");datasicaklik(10);
tft.setCursor(0,satiraralik*10);datazaman1(11);tft.setTextColor(0x6043,0xffff);tft.print(" ");datasicaklik(11);
tft.setCursor(0,satiraralik*11);datazaman1(12);tft.setTextColor(0x6043,0xffff);tft.print(" ");datasicaklik(12);
  }
}

int altyazitft2(int satiraralik){
t2=now();
tft.setTextColor(0x000,0x17e9); tft.setTextSize(4);
if ( i< 240){
tft.setCursor(i,satiraralik*12);tft.print(" Dolar=");dolar();tft.print(" AltinOns=");altin("XAU");
tft.setTextColor(0x0000, 0x17e9); tft.setTextSize(4);
tft.print("|SAAT ");if (hour(t2) < 10)tft.print("0");tft.print(hour(t2));tft.print(":");if (minute(t2) < 10)tft.print("0");tft.print(minute(t2));
i=i+1;
}else{
tft.setTextColor(0x0000, 0x17e9);
tft.setCursor(0,satiraralik*12);tft.print("              ");
i=-600;
}
}
int zamanal(){
timeClient.update();
timeClient.setTimeOffset(3600+3600+3600);
t2 = timeClient.getEpochTime();
setTime(t2);
}
int donguzaman(int saniye){
  t2=now();
  if((t2-t3)>=saniye){
    n=n+1;
   Serial.println(t2);
   Serial.print("WiFi.status()");Serial.println(WiFi.status());
   if ((WiFi.status() == 3)&& n>=3){n=0; doc.clear(); doc1.clear();}
   t3=t2;
  }
}

void loop()
{


if ((WiFi.status() == WL_CONNECTED)&& n==0) { //Check WiFi connection status
Serial.print("http datasi alinacak");Serial.print("n=>");Serial.println(n);
zamanal();
HTTPClient http;  //Declare an object of class HTTPClient
http.begin("http://api.openweathermap.org/data/2.5/forecast?lat=39.966477&lon=32.879326&APPID=3d183cadc635fb5328f1eb40606ae0df&units=metric");  //Specify request destination
int httpCode = http.GET();                                                                  //Send the request
if (httpCode > 0) { //Check the returning code
String aa = http.getString();   //Get the request response payload
deserializeJson(doc,aa);//yenibilgi2019-12 :
havatft2(17); 
}
http.end(); 
delay(100);
HTTPClient http1; 
http1.begin("http://openexchangerates.org/api/latest.json?app_id=e4e7bd163f154335aa60224d0fc2ae01");  //Specify request destination
int httpCode1 = http1.GET(); 
if (httpCode1 > 0) {
String bb = http1.getString(); 
deserializeJson(doc1,bb);
}
http1.end();

n=n+1; 
}
//

//
altyazitft2(17);
//Serial.print("WiFi.status()");Serial.println(WiFi.status());
Serial.print("n=>");Serial.println(n);

}

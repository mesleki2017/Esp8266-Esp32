#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <TimeLib.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

#define TFT_CS D0  //for D1 mini or TFT I2C Connector Shield (V1.1.0 or later)
#define TFT_DC D8  //for D1 mini or TFT I2C Connector Shield (V1.1.0 or later)
#define TFT_RST -1 //for D1 mini or TFT I2C Connector Shield (V1.1.0 or later)
#define TS_CS D3   //for D1 mini or TFT I2C Connector Shield (V1.1.0 or later)

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
////////////////////////////////////////
int n=0;
String a;
String b;
String c;
String d;
String f;
#define LINECOLOR1 0xEBD5
#define mavi1 0x21CE
#define mavi2 0x2AB6
#define mavi3 0x3319
#define mavi4 0x43DF
#define sari1 0xDF88
int renk;
int sicaklik;
int i = 0;
///////////////////////////////
const char* ssid = "GM 9 Pro";
const char* password = "asdf12345678";
DynamicJsonDocument doc(16000);
String payload;
/////////////////////////////////////////
time_t t1=0;
time_t t2=0;
time_t t3=0;
char *ay[]={"","Ocak","Subat","Mart","Nisan","Mayis","Haziran","Temmuz","Agustos","Eylul","Ekim","Kasim","Aralik"};
char* gun[]={"","Pzr","Pzrt","Sl","Crsmb","Prsmb","Cm","Cmrts"};
//char* gun[]={"","Pazar","Pazartesi","Sali","Carsamba","Persembe","Cuma","Cumartesi"};
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);
void setup()
{
  Serial.begin(115200);
  timeClient.begin();
  Serial.println("ILI9341 Test!");
  tft.begin();
  tft.setRotation(1);
  tft.setTextColor(ILI9341_YELLOW, ILI9341_RED); tft.setTextSize(2);
  tft.fillRect(0,0, 320,120, ILI9341_WHITE);
  tft.fillRect(0,120,320,240, ILI9341_GREEN);
  tft.fillCircle(0,0,10,ILI9341_BLACK);tft.fillCircle(320,0,10,ILI9341_RED);
  tft.fillCircle(0,240,10,ILI9341_YELLOW);tft.fillCircle(320,240,10,ILI9341_PURPLE);
  tft.fillCircle(0,120,10,ILI9341_YELLOW);tft.fillCircle(320,120,10,ILI9341_PURPLE);
  tft.fillCircle(160,120,10,ILI9341_YELLOW);
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
Serial.print("Connecting..");
tft.setCursor(10, 10);tft.print("baglaniyor");
delay(1000);
}
tft.setCursor(10, 10);tft.println("baglandi..");
delay(1000);

}

void loop()
{
if ((WiFi.status() == WL_CONNECTED)&& n==0) { //Check WiFi connection status
 
HTTPClient http;  //Declare an object of class HTTPClient
 
http.begin("http://api.openweathermap.org/data/2.5/forecast?lat=39.966477&lon=32.879326&APPID=3d183cadc635fb5328f1eb40606ae0df&units=metric");  //Specify request destination
int httpCode = http.GET();                                                                  //Send the request
 
if (httpCode > 0) { //Check the returning code
 
String aa = http.getString();   //Get the request response payload
timeClient.update();
Serial.println(" ");
Serial.println(aa);
Serial.println("*********************************");
deserializeJson(doc,aa);//Print the response payload

serializeJson(doc["list"][20]["dt"], a);
serializeJson(doc["list"][0]["main"]["temp"], b);

//Serial.print("a=>");Serial.println(a);
//Serial.print("b=>");Serial.println(b);


timeClient.setTimeOffset(3600+3600+3600);
t2 = timeClient.getEpochTime();
setTime(t2);
t3=now();

}

http.end();   //Close connection
n=n+1;
}
t2=now();

if ( (t2 - t3)>= 1 ) {
    //Serial.print("t2-t3=> ");Serial.println(t2-t3);

    t3=t2;


if (i <= 26){i=i+1;}else{i=0;}

a="";b="";

serializeJson(doc["list"][i]["dt"], a);
serializeJson(doc["list"][i]["main"]["temp"], b);
t1=a.toInt();
sicaklik=b.toInt();

if ( 0<sicaklik*100 && 800>sicaklik*100 ){renk=mavi1;}
if (-200<sicaklik*100 && 0>sicaklik*100){renk=mavi2;}
if (-400<sicaklik*100 && -200>sicaklik*100){renk=mavi3;}
if (-600<sicaklik*100 && -400>sicaklik*100){renk=mavi4;}
//tft.fillRect(0,0, 320,120, renk);
tft.setTextColor(sari1, renk); tft.setTextSize(4);//yenibilgi https://forum.arduino.cc/index.php?topic=364055.0
//tft.setCursor(10,10);tft.print(" ");tft.print(day(t1));tft.print("-");tft.print(ay[month(t1)]);tft.print(" ");tft.print(hour(t1));tft.print(":00");tft.print(" ");
tft.setCursor(10,10);tft.print("");tft.print(gun[weekday(t1)]);tft.print("    ");
tft.setCursor(180,10);if (hour(t1) < 10)tft.print("0");tft.print(hour(t1));tft.print(":00");
tft.setTextColor(renk, ILI9341_WHITE);tft.setTextSize(4);
tft.setCursor(10,50);tft.print(" ");tft.print(b);tft.print(" C");tft.print(char(167));;tft.print(" ");
//tft.fillRect(0,110, 320,130, sari1);
tft.setTextColor(ILI9341_BLACK, ILI9341_GREEN); tft.setTextSize(6);
tft.setCursor(10,140);if (hour(t2) < 10)tft.print("0");tft.print(hour(t2));tft.print(":");if (minute(t2) < 10)tft.print("0");tft.print(minute(t2));tft.print(":");if (second(t2) < 10)tft.print("0");tft.print(second(t2));

}


}

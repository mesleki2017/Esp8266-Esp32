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

// #define TFT_CS 14  //for D32 Pro
// #define TFT_DC 27  //for D32 Pro
// #define TFT_RST 33 //for D32 Pro
// #define TS_CS  12 //for D32 Pro

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
///////////////////////////////
const char* ssid = "Kablonet Netmaster-DAEB-G";
const char* password = "c6f6b680";
DynamicJsonDocument doc(16000);
String payload;
/////////////////////////////////////////
time_t t1=0;
time_t t2=0;
time_t t3=0;
char *ay[]={"","Ocak","Subat","Mart","Nisan","Mayis","Haziran","Temmuz","Agustos","Eylul","Ekim","Kasim","Aralik"};
char* gun[]={"","Pazar","Pazartesi","Sali","Carsamba","Persembe","Cuma","Cumartesi"};
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);
void setup()
{
  Serial.begin(115200);
  timeClient.begin();
  Serial.println("ILI9341 Test!");
  tft.begin();
  tft.setRotation(1);tft.fillScreen(ILI9341_BLUE);
  tft.setTextColor(ILI9341_YELLOW, ILI9341_RED); tft.setTextSize(2);
  tft.fillRect(0,0, 320,120, ILI9341_RED);
  tft.fillRect(0,120,320,240, ILI9341_GREEN);
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

Serial.print("a=>");Serial.println(a);
Serial.print("b=>");Serial.println(b);


timeClient.setTimeOffset(3600+3600+3600);
t2 = timeClient.getEpochTime();
setTime(t2);

}

http.end();   //Close connection
n=n+1;
 
}


for (int i = 0; i <= 26; i++){
a="";b="";

serializeJson(doc["list"][i]["dt"], a);
serializeJson(doc["list"][i]["main"]["temp"], b);
t1=a.toInt();
sicaklik=b.toInt();

if ( 0<sicaklik*100 && 800>sicaklik*100 ){renk=mavi1;}
if (-200<sicaklik*100 && 0>sicaklik*100){renk=mavi2;}
if (-400<sicaklik*100 && -200>sicaklik*100){renk=mavi3;}
if (-600<sicaklik*100 && -400>sicaklik*100){renk=mavi4;}
tft.fillRect(0,0, 320,120, renk);
tft.setTextColor(ILI9341_RED, renk); tft.setTextSize(3);//yenibilgi https://forum.arduino.cc/index.php?topic=364055.0
tft.setCursor(10,10);tft.print(" ");tft.print(day(t1));tft.print("-");tft.print(ay[month(t1)]);tft.print(" ");tft.print(hour(t1));tft.print(":00");tft.print(" ");
tft.setCursor(10,45);tft.print(" ");tft.print(gun[weekday(t1)]);tft.print("      ");
tft.setTextColor(ILI9341_YELLOW, renk);
tft.setCursor(10,90);tft.print("  ");tft.print(b);tft.print(" derece ");


t2=now();
tft.setTextColor(ILI9341_BLACK, ILI9341_GREEN); tft.setTextSize(3);
tft.setCursor(10,180);if (hour(t2) < 10)tft.print("0");tft.print(hour(t2));tft.print(":");if (minute(t2) < 10)tft.print("0");tft.print(minute(t2));tft.print(":");if (second(t2) < 10)tft.print("0");tft.print(second(t2));

delay(900);
}


}

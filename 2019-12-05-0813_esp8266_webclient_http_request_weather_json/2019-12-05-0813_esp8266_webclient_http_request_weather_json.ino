#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

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
#define LINECOLOR1 0xEBD5
///////////////////////////////
const char* ssid = "GM 9 Pro";
const char* password = "asdf12345678";
DynamicJsonDocument doc(3000);
String payload;
/////////////////////////////////////////
void setup()
{
  Serial.begin(115200);
  Serial.println("ILI9341 Test!");
  tft.begin();
  tft.setRotation(1);tft.fillScreen(ILI9341_BLUE);
  tft.setTextColor(ILI9341_YELLOW, ILI9341_RED); tft.setTextSize(2);
  tft.fillRect(4,4, 315,100, ILI9341_RED);
  tft.fillRect(4,100, 315,235, ILI9341_GREEN);
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
 
http.begin("http://api.weatherstack.com/forecast?access_key=03e58b4fa98fad9a76929331658a158d&query=39.966477,32.879326");  //Specify request destination
int httpCode = http.GET();                                                                  //Send the request
 
if (httpCode > 0) { //Check the returning code
 
String aa = http.getString();   //Get the request response payload
Serial.println(" ");
Serial.println(aa);
Serial.println("*********************************");
deserializeJson(doc,aa);//Print the response payload

serializeJson(doc["current"]["temperature"], a);
serializeJson(doc["current"]["weather_descriptions"][0], b);
serializeJson(doc["current"]["humidity"], c);
serializeJson(doc["current"]["wind_speed"], d);
Serial.print("a=>");Serial.println(a);
Serial.print("b=>");Serial.println(b);
Serial.print("c=>");Serial.println(c);
Serial.print("c=>");Serial.println(d);

}

http.end();   //Close connection
n=n+1;
 
}
tft.setTextColor(ILI9341_YELLOW, ILI9341_RED); tft.setTextSize(3);//yenibilgi https://forum.arduino.cc/index.php?topic=364055.0
tft.setCursor(10,10);tft.print("sicaklik");
tft.setCursor(10,40);tft.print(a);
// tft.drawLine(10, 45, 50,45, ILI9341_BLACK);
////////////////////////////////
tft.setTextColor(ILI9341_BLACK, ILI9341_GREEN); tft.setTextSize(3);
tft.setCursor(10,110);tft.print("durum     *");
tft.setCursor(10,140);tft.print(b);
////////////////////////////////
delay(900);
////////////////////////////////
tft.setCursor(10,110);tft.print("Nemlilik      *");
tft.setCursor(10,140);tft.print(c);tft.print("             ");
delay(900);
////////////////////////////////
tft.setCursor(10,110);tft.print("Ruzgar hizi");
tft.setCursor(10,140);tft.print(d);tft.print("             ");
delay(900);

}

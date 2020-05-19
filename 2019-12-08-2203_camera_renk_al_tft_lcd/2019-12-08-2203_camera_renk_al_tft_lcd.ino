#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
//#include <WiFiClientSecure.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266WebServerSecure.h>
#include <ESP8266mDNS.h>
#include <FS.h> 
#include <TimeLib.h>



#define TFT_CS D0  //for D1 mini or TFT I2C Connector Shield (V1.1.0 or later)
#define TFT_DC D8  //for D1 mini or TFT I2C Connector Shield (V1.1.0 or later)
#define TFT_RST -1 //for D1 mini or TFT I2C Connector Shield (V1.1.0 or later)
#define TS_CS D3   //for D1 mini or TFT I2C Connector Shield (V1.1.0 or later)

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
////////////////////////////////////////

//Enter your SSID and PASSWORD
const char* ssid = "ESP8266";
const char* password = "12345678";
ESP8266WebServer server(80); 
///////////////////////////////////////77
int x=0;
int y=0;


void handleJSData(){
  boolean yDir;
  x = server.arg(0).toInt() * 10;
  y = server.arg(1).toInt() * 10;
  Serial.print("x =>");Serial.println(x);
  Serial.print("y =>");Serial.println(y);

server.send(200, "text/plain","deneme1");

 tft.fillCircle(160,120,120,x*10-y*10);
 tft.setTextColor(ILI9341_RED, x*10);
 tft.setCursor(10,200);tft.print("x = ");tft.print(x);
 
}

void setup()
{
  Serial.begin(115200);

  tft.begin();
  tft.setRotation(1);
  tft.setTextColor(ILI9341_YELLOW, ILI9341_RED); tft.setTextSize(2);
  tft.fillRect(0,0, 320,120, ILI9341_WHITE);
  tft.fillRect(0,120,320,240, ILI9341_GREEN);
  
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();

tft.setCursor(10, 10);tft.println("baglandi..");
delay(1000);
Serial.println("IP address: ");
Serial.println(WiFi.localIP());
  if (!SPIFFS.begin()){
    Serial.println("SPIFFS Mount failed");
  } 
  else {
    Serial.println("SPIFFS Mount succesfull");
  }
 ////////////////////////////////////////////////////////
 File file6 = SPIFFS.open("/index.html", "r");///deneme
  if(file6){
    Serial.println("index.html acildi");
  }
   File file7 = SPIFFS.open("/tracking-min.js", "r");///deneme
  if(file7){
    Serial.println("tracking-min.js acildi");
  }
     File file8 = SPIFFS.open("/deneme5.html", "r");///deneme
  if(file8){
    Serial.println("deneme5.html acildi");
  }
      File file9 = SPIFFS.open("/tracking.js", "r");///deneme
  if(file9){
    Serial.println("tracking.js acildi");
  }
  server.serveStatic("/", SPIFFS, "/index.html"); 
  server.serveStatic("/tracking.js", SPIFFS, "/tracking.js");
  server.serveStatic("/tracking-min.js", SPIFFS, "/tracking-min.js");
  server.serveStatic("/deneme5.html", SPIFFS, "/deneme5.html");
  //call handleJSData function when this URL is accessed by the js in the html file
 
 server.on("/jsData.html", handleJSData); 
 server.begin();
  
}


void loop(void)
{
 server.handleClient();



}

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>
#include <FS.h> 
#include <TimeLib.h>


#define TFT_CS D0  //for D1 mini or TFT I2C Connector Shield (V1.1.0 or later)
#define TFT_DC D8  //for D1 mini or TFT I2C Connector Shield (V1.1.0 or later)
#define TFT_RST -1 //for D1 mini or TFT I2C Connector Shield (V1.1.0 or later)
#define TS_CS D3   //for D1 mini or TFT I2C Connector Shield (V1.1.0 or later)

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
////////////////////////////////////////
const char* ssid = "Kablonet Netmaster-DAEB-G";
const char* password = "c6f6b680";
///////////////////////////////////////77
int x=0;
int y=0;

ESP8266WebServer server (80);
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
WiFi.mode(WIFI_STA);
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
Serial.print("Connecting..");
tft.setCursor(10, 10);tft.print("baglaniyor");
delay(1000);
}
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
 File file6 = SPIFFS.open("/joystick.html", "r");///deneme
  if(file6){
    Serial.println("joystick.html acildi");
  }
   File file7 = SPIFFS.open("/virtualjoystick.js", "r");///deneme
  if(file7){
    Serial.println("virtualjoystick.js acildi");
  }
   
  server.serveStatic("/", SPIFFS, "/joystick.html"); 
  server.serveStatic("/virtualjoystick.js", SPIFFS, "/virtualjoystick.js");
  //call handleJSData function when this URL is accessed by the js in the html file
  server.begin();
  server.on("/jsData.html", handleJSData);  
  
}

void loop(void)
{
 server.handleClient(); 


}

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
//#include <Fonts/FreeSansOblique9pt7b.h>



#include <ESP8266HTTPClient.h>

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <FS.h> 
#include <ArduinoJson.h>
#include <TimeLib.h>
#include <Adafruit_NeoPixel.h>


////////////////////////////////////////////////////////////////
#define TFT_CS D0  //for D1 mini or TFT I2C Connector Shield (V1.1.0 or later)
#define TFT_DC D8  //for D1 mini or TFT I2C Connector Shield (V1.1.0 or later)
#define TFT_RST -1 //for D1 mini or TFT I2C Connector Shield (V1.1.0 or later)
#define TS_CS D3   //for D1 mini or TFT I2C Connector Shield (V1.1.0 or later)
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
#define ENCODING_END 255
//////////////////////////////////////////////////////////


int alinanRcolorSag=0;


String javasciptenRenkText6;
String gelenyazi1;
ESP8266WebServer server(80);

//Enter your SSID and PASSWORD
const char* ssid = "ESP8266";
const char* password = "12345678";


///////////////////////////////

void espyeRcolorAlSag() {
javasciptenRenkText6 = server.arg("RcolorSag"); //Refer  xhttp.open("GET", "setLED?xxx="+today.getTime(), true)
 alinanRcolorSag=javasciptenRenkText6.toInt();
Serial.print("alinanRcolortSol=> ");Serial.println(alinanRcolorSag);
String str1="RcolorAlindiSag";
server.send(200, "text/plane",str1 ); 
 tft.fillRect(0,0, 320,240, alinanRcolorSag);
 tft.setCursor(0,12*1),tft.print(alinanRcolorSag);
}

void espyeYaziAl() {
gelenyazi1 = server.arg("espyeGelenYazi"); //Refer  xhttp.open("GET", "setLED?xxx="+today.getTime(), true)
Serial.print("espyeGelenYazi=> ");Serial.println(gelenyazi1);
String str1="yazi1alindi";
server.send(200, "text/plane",str1 ); 
tft.setTextSize(4);
tft.setTextColor(0xffff,alinanRcolorSag-500);
tft.fillRect(0,0, 320,240, alinanRcolorSag);
tft.setCursor(0,12*1),tft.print(gelenyazi1);
}



////////////////////////////
void setup(void){
  //////////////////////////////////////////
  tft.begin();
  tft.setRotation(1);
  tft.setTextWrap(false);//yenibilgi2019-12-11:yazi satiri doldurdugunda asagi gecmesin
  tft.setTextColor(0x0000,0xffff); tft.setTextSize(2);
  tft.fillRect(0,0, 320,120, 0xffff);
 
  tft.fillRect(0,120,320,240,0xffff );
  //tft.setFont(&FreeSansOblique9pt7b);
  ///////////////////////////////////////////
  ESP.eraseConfig();//2019-12-19yeni esp zaman zaman wifi server uzerinden gerekli dosyalara tam bağlanamiyordu. bazen iyi bazen kotu idi. belki bu cozum olur.emin degilim
  Serial.begin(115200);
  SPIFFS.begin();
  if(SPIFFS.begin()){
     Serial.println("SPIFFS dosya sistemi aktif");
    //return;
  }
 
      File file2 = SPIFFS.open("/index.html", "r");
  if(file2){
    Serial.println("index.html acildi");
   
  }

   
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  
  server.serveStatic("/", SPIFFS, "/index.html"); 
  server.on("/RcolorAlSag", espyeRcolorAlSag);  
  server.on("/YaziAl",espyeYaziAl);  
  setTime(1000);
  server.begin();
  delay(2000);
  Serial.println("setupbitti");
}
  
void loop(void){
 server.handleClient(); 

}

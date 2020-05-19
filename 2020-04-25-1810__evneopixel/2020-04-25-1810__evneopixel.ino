
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <FS.h> 
#include <ArduinoJson.h>
#include <TimeLib.h>
#include <Adafruit_NeoPixel.h>


#define PIN        D3 
#define NUMPIXELS 24

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ400);


int alinanRcolorSag=0;


String javasciptenRenkText6;
String javasciptenRenkText7;
ESP8266WebServer server(80);

//Enter your SSID and PASSWORD
const char* ssid = "ESP8266";
const char* password = "12345678";


///////////////////////////////

void espyeRcolorAlSag() {
javasciptenRenkText6 = server.arg("RcolorSag"); //Refer  xhttp.open("GET", "setLED?xxx="+today.getTime(), true)
 alinanRcolorSag=javasciptenRenkText6.toInt();
Serial.print("alinanRcolortSol=> ");Serial.println(alinanRcolorSag);
pixels.setPixelColor(12, pixels.Color(255,0,0));
String str1="RcolorAlindiSag";
server.send(200, "text/plane",str1 ); 
pixels.fill(alinanRcolorSag);
pixels.setBrightness(100);

pixels.show();

}


////////////////////////////



void setup(void){
 
  ESP.eraseConfig();//2019-12-19yeni esp zaman zaman wifi server uzerinden gerekli dosyalara tam bağlanamiyordu. bazen iyi bazen kotu idi. belki bu cozum olur.emin degilim
  Serial.begin(115200);
  SPIFFS.begin();
  if(SPIFFS.begin()){
     Serial.println("SPIFFS dosya sistemi aktif");
    //return;
  }
  
    File file1 = SPIFFS.open("/jscolor.js", "r");
  if(file1){
    Serial.println("jscolor.js acildi");
   
  }
      File file2 = SPIFFS.open("/index.html", "r");
  if(file2){
    Serial.println("index.html acildi");
   
  }

   
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  
  server.serveStatic("/", SPIFFS, "/index.html"); 
  server.serveStatic("/jscolor.js", SPIFFS, "/jscolor.js");

  server.on("/RcolorAlSag", espyeRcolorAlSag);

  
  setTime(1000);
  server.begin();
  delay(2000);
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  Serial.println("setupbitti");
}
  
void loop(void){
 server.handleClient(); 


}


#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <FS.h> 
#include <ArduinoJson.h>
#include <TimeLib.h>
#include <Adafruit_NeoPixel.h>

#define PIN        D3 
#define NUMPIXELS 24

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int alinanRcolorSol=0;
int alinanGcolorSol=0;
int alinanBcolorSol=0;
int alinanRcolorSag=0;
int alinanGcolorSag=0;
int alinanBcolorSag=0;

String javasciptenRenkText1;
String javasciptenRenkText2;
String javasciptenRenkText3;
String javasciptenRenkText4;
String javasciptenRenkText5;
String javasciptenRenkText6;

ESP8266WebServer server(80);

//Enter your SSID and PASSWORD
const char* ssid = "ESP8266";
const char* password = "12345678";



void espyeRcolorAlSol() {
 
javasciptenRenkText1 = server.arg("RcolorSol"); //Refer  xhttp.open("GET", "setLED?xxx="+today.getTime(), true)
 alinanRcolorSol=javasciptenRenkText1.toInt();
 Serial.print("alinanRcolortSol=> ");Serial.println(alinanRcolorSol);
String str1="RcolorAlindiSol";
server.send(200, "text/plane",str1 ); 
}
void espyeGcolorAlSol() {
javasciptenRenkText2 = server.arg("GcolorSol"); //Refer  xhttp.open("GET", "setLED?xxx="+today.getTime(), true)
 alinanGcolorSol=javasciptenRenkText2.toInt();
Serial.print("alinanGcolortSol=> ");Serial.println(alinanGcolorSol);
String str1="GcolorAlindiSol";
server.send(200, "text/plane",str1 ); 
}
void espyeBcolorAlSol() {
javasciptenRenkText3 = server.arg("BcolorSol"); //Refer  xhttp.open("GET", "setLED?xxx="+today.getTime(), true)
 alinanBcolorSol=javasciptenRenkText3.toInt();
Serial.print("alinanBcolortSol=> ");Serial.println(alinanBcolorSol);
String str1="BcolorAlindiSol";
server.send(200, "text/plane",str1 ); 
for(int i=0; i<12; i++) {
  pixels.setPixelColor(i, pixels.Color(alinanRcolorSol,alinanGcolorSol,alinanBcolorSol));
  pixels.show();
}
}
///////////////////////////////
void espyeRcolorAlSag() {
javasciptenRenkText4 = server.arg("RcolorSag"); //Refer  xhttp.open("GET", "setLED?xxx="+today.getTime(), true)
 alinanRcolorSag=javasciptenRenkText4.toInt();
 Serial.print("**///**=> ");Serial.println(alinanRcolorSag);
String str1="RcolorAlindiSag";
server.send(200, "text/plane",str1 ); 
}
void espyeGcolorAlSag() {
javasciptenRenkText5 = server.arg("GcolorSag"); //Refer  xhttp.open("GET", "setLED?xxx="+today.getTime(), true)
 alinanGcolorSag=javasciptenRenkText5.toInt();
Serial.print("alinanGcolortSag=> ");Serial.println(alinanGcolorSag);
String str1="GcolorAlindiSag";
server.send(200, "text/plane",str1 ); 
}
void espyeBcolorAlSag() {
javasciptenRenkText6 = server.arg("BcolorSag"); //Refer  xhttp.open("GET", "setLED?xxx="+today.getTime(), true)
 alinanBcolorSag=javasciptenRenkText6.toInt();
Serial.print("alinanBcolortSol=> ");Serial.println(alinanBcolorSag);
pixels.setPixelColor(12, pixels.Color(255,0,0));
String str1="BcolorAlindiSag";
server.send(200, "text/plane",str1 ); 
for(int i=12; i<24; i++) {
  pixels.setPixelColor(i, pixels.Color(alinanRcolorSag,alinanGcolorSag,alinanBcolorSag));
  pixels.show();
}
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

  server.on("/RcolorAlSol", espyeRcolorAlSol);
  server.on("/GcolorAlSol", espyeGcolorAlSol);
  server.on("/BcolorAlSol", espyeBcolorAlSol);

  server.on("/RcolorAlSag", espyeRcolorAlSag);
  server.on("/GcolorAlSag", espyeGcolorAlSag);
  server.on("/BcolorAlSag", espyeBcolorAlSag);
  
  setTime(1000);
  server.begin();
  delay(2000);
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  Serial.println("setupbitti");
}
  
void loop(void){
 server.handleClient(); 


}

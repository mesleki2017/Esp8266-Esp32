
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

int alinanRcolor=0;
int alinanGcolor=0;
int alinanBcolor=0;

String javasciptenRenkText;// javasciptenRenkText i daha once local yapmistim espyeZamanAl in icindei her fonksiyon tetiklendiginde O landi
String javasciptenRenkText2;
String javasciptenRenkText3;
ESP8266WebServer server(80);

//Enter your SSID and PASSWORD
const char* ssid = "ESP8266";
const char* password = "12345678";



void espyeRcolorAl() {
 
 javasciptenRenkText = server.arg("Rcolor"); //Refer  xhttp.open("GET", "setLED?xxx="+today.getTime(), true)
 alinanRcolor=javasciptenRenkText.toInt();
// javasciptenRenkText2 = server.arg("Gcolor"); //Refer  xhttp.open("GET", "setLED?xxx="+today.getTime(), true)
 //alinanGcolor=javasciptenRenkText2.toInt();
 Serial.print("alinanRcolort=> ");Serial.println(alinanRcolor);

String str1="RcolorAlindi";
server.send(200, "text/plane",str1 ); //Send web page
//http://192.168.4.1/zamanAl sayfasina str1 yazar

}
void espyeGcolorAl() {
 javasciptenRenkText2 = server.arg("Gcolor"); //Refer  xhttp.open("GET", "setLED?xxx="+today.getTime(), true)
 alinanGcolor=javasciptenRenkText2.toInt();
Serial.print("alinanGcolort=> ");Serial.println(alinanGcolor);
String str1="GcolorAlindi";
server.send(200, "text/plane",str1 ); 
}
void espyeBcolorAl() {
 javasciptenRenkText3 = server.arg("Bcolor"); //Refer  xhttp.open("GET", "setLED?xxx="+today.getTime(), true)
 alinanBcolor=javasciptenRenkText3.toInt();
Serial.print("alinanBcolort=> ");Serial.println(alinanBcolor);
String str1="BcolorAlindi";
server.send(200, "text/plane",str1 ); 
pixels.clear();
for(int i=0; i<NUMPIXELS; i++) {
  pixels.setPixelColor(i, pixels.Color(alinanRcolor,alinanGcolor,alinanBcolor));
  pixels.show();
}
}
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

  server.on("/RcolorAl", espyeRcolorAl);
  server.on("/GcolorAl", espyeGcolorAl);
  server.on("/BcolorAl", espyeBcolorAl);
  setTime(1000);
  server.begin();
  delay(2000);
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  Serial.println("setupbitti");
}
  
void loop(void){
 server.handleClient(); 


}

//https://circuits4you.com/2018/02/04/esp8266-ajax-update-part-of-web-page-without-refreshing/
// telefonda ki web arayuzu index.h dosyasinda yazdik. bu programla ayni klasorde
//https://stackoverflow.com/questions/18310434/how-to-set-text-size-in-a-button-in-html
//h1 le ilgili https://www.w3schools.com/tags/tag_hn.asp;
//https://techtutorialsx.com/2016/10/03/esp8266-setting-a-simple-http-webserver/
//https://www.w3schools.com/jsref/met_win_setinterval.asp
//https://stackoverflow.com/questions/6032429/chrome-timeouts-interval-suspended-in-background-tabs // chrome da neden javascritp setinterval da problem yasadigimin cevabi
//https://www.w3schools.com/css/tryit.asp?filename=trycss_grid
//#include <WiFi.h>
//#include <WiFiClient.h>
//#include <WebServer.h>

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <OneWire.h>
#include <DallasTemperature.h>
 
#include "index.h"  //Web page header file
#include "d3.h"

#define ONE_WIRE_BUS 5                          //D1 pin of nodemcu
OneWire oneWire(ONE_WIRE_BUS);
 DallasTemperature sensors(&oneWire);            // Pass the oneWire reference to Dallas Temperature.


String ledState = "OFF";





 
ESP8266WebServer server(80);
 
//Enter your SSID and PASSWORD
const char* ssid = "ESP8266";
const char* password = "12345678";



 
//===============================================================
// This routine is executed when you open its IP in browser
//===============================================================
void handleRoot() {
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
 Serial.println("handleRoot");
}
void handleADC00() {
  sensors.requestTemperatures();
 float a = sensors.getTempCByIndex(0);
 String adcValue00 = String(a);
 //String adcValue00 = "deger1";
 server.send(200, "text/plane", adcValue00); //Send ADC value only to client ajax request
 Serial.println("handleADC00");
}





void handleLED() {
 
 String t_state = server.arg("LEDstate"); //Refer  xhttp.open("GET", "setLED?LEDstate="+led, true);
 Serial.println(t_state);
 if(t_state == "1")
 {
  digitalWrite(2,LOW); //LED ON
  ledState = "ON"; //Feedback parameter
 }
 else
 {
  digitalWrite(2,HIGH); //LED OFF
  ledState = "OFF"; //Feedback parameter  
 }
 
 server.send(200, "text/plane", ledState); //Send web page
 Serial.println("handleLED");
}

//===============================================================
// Setup
//===============================================================
 
void setup(void){
  pinMode(2,OUTPUT);
  Serial.begin(115200);



  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();

  
  server.begin();

//----------------------------------------------------------------
 
  server.on("/", handleRoot);      //Which routine to handle at root location. This is display page
  server.on("/setLED", handleLED);
  server.on("/readADC00", handleADC00);



}
 
//===============================================================
// This routine is executed when you open its IP in browser
//===============================================================
void loop(void){

  
  server.handleClient();


  
}

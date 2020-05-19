//https://circuits4you.com/2018/02/04/esp8266-ajax-update-part-of-web-page-without-refreshing/
// telefonda ki web arayuzu index.h dosyasinda yazdik. bu programla ayni klasorde
//https://stackoverflow.com/questions/18310434/how-to-set-text-size-in-a-button-in-html


#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <OneWire.h>
#include <DallasTemperature.h>
 
#include "index.h"  //Web page header file

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
void handleADC() {
  sensors.requestTemperatures();
 float a = sensors.getTempCByIndex(0);
 String adcValue = String(a);
 //String adcValue00 = "deger1";
 server.send(200, "text/plane", adcValue); //Send ADC value only to client ajax request
Serial.println(a);
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

  server.on("/readADC", handleADC);



}
 
//===============================================================
// This routine is executed when you open its IP in browser
//===============================================================
void loop(void){

  
  server.handleClient();


  
}

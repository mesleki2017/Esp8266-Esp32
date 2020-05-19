
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <FS.h> 
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 5                          //D1 pin of nodemcu
OneWire oneWire(ONE_WIRE_BUS);
 DallasTemperature sensors(&oneWire);            // Pass the oneWire reference to Dallas Temperature.





ESP8266WebServer server(80); 
//Enter your SSID and PASSWORD
const char* ssid = "ESP8266";
const char* password = "12345678";

void handleADC00() {
  sensors.requestTemperatures();
 float a = sensors.getTempCByIndex(0);
 String adcValue00 = String(a);
 //String adcValue00 = "deger1";
 server.send(200, "text/plane", adcValue00); //Send ADC value only to client ajax request
 Serial.println("handleADC00");
}

void setup(void){
  pinMode(2,OUTPUT);
  Serial.begin(115200);
  SPIFFS.begin();
  if(SPIFFS.begin()){
     Serial.println("SPIFFS dosya sistemi aktif");
    //return;
  }
    File file1 = SPIFFS.open("/d3.min.js", "r");
  if(file1){
    Serial.println("file1 acildi");
   
  }
      File file2 = SPIFFS.open("/2019-10-02-1316.html", "r");
  if(file2){
    Serial.println("file2 acildi");
   
  }
   
      File file3 = SPIFFS.open("/data111.csv", "r");
  if(file3){
    Serial.println("file3 acildi");
   
  }
   
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();

  server.serveStatic("/", SPIFFS, "/2019-10-02-1316.html"); 
  server.serveStatic("/d3.min.js", SPIFFS, "/d3.min.js");
  server.serveStatic("/data111.csv", SPIFFS, "/data111.csv");
  server.on("/readADC00", handleADC00);
  server.begin();

}


void loop(void){
  server.handleClient();  
}

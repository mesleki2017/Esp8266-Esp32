
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <FS.h> 
#include <OneWire.h>
#include <DallasTemperature.h>
#include <ArduinoJson.h>

unsigned long intervalHist = 5000;
float t;

#define ONE_WIRE_BUS 5                          //D1 pin of nodemcu
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);            // Pass the oneWire reference to Dallas Temperature.



StaticJsonDocument<4400> jsonBuffer;
JsonObject root = jsonBuffer.as<JsonObject>(); 

JsonArray timestamp = root.createNestedArray("timestamp");
JsonArray hist_t = root.createNestedArray("t");
char json[4400];

void addPtToHist(){
  unsigned long currentMillis = millis();
  unsigned long previousMillis ;
  if ( currentMillis - previousMillis > intervalHist ) {
    previousMillis = currentMillis;
    timestamp.add(currentMillis/1000/60);
    sensors.requestTemperatures();
    float a = sensors.getTempCByIndex(0);
    String t = String(a);
    Serial.print("t-----------");Serial.println(t);
    Serial.print("currentMillis****************");Serial.println(currentMillis);
    hist_t.add(t);
    if ( hist_t.size() > 40 ) {
      //Serial.println("efface anciennes mesures");
      timestamp.remove(0);
      hist_t.remove(0);
    } 
    saveHistory();
  }
}

void loadHistory(){
  File file5 = SPIFFS.open("/data111.json", "r");  
  if (!file5){
    Serial.println("No History Exist");
  } else {
    size_t size = file5.size();
    Serial.println(size);
    if ( size == 0 ) {
      Serial.println(" data11.json file empty !");
    } else {
      std::unique_ptr<char[]> buf (new char[size]);
      file5.readBytes(buf.get(), size);
      deserializeJson(jsonBuffer,buf.get() );
      if (!deserializeJson(jsonBuffer,buf.get())) {
        Serial.println("Impossible de lire le JSON - Impossible to read JSON file");
      } else {
        //Serial.println(file5.readBytes(buf.get(), size));
        Serial.println(file5.readBytes(buf.get(), 100));
        serializeJson(jsonBuffer, file5);
      }
    }
    file5.close();
  }
}
void saveHistory(){ 
  File file4 = SPIFFS.open("/data111.json", "w");         

  //root.printTo(file4); // Exporte et enregsitre le JSON dans la zone SPIFFS - Export and save JSON object to SPIFFS area
  serializeJson(jsonBuffer, file4);
  Serial.print("file4.size()========================");Serial.println(file4.size());
  file4.close();  
}


ESP8266WebServer server(80); 
//Enter your SSID and PASSWORD
const char* ssid = "ESP8266";
const char* password = "12345678";



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
   
      File file3 = SPIFFS.open("/data111.json", "r");
  if(file3){
    Serial.println("file3 acildi");
   
  }
   
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();

  server.serveStatic("/", SPIFFS, "/2019-10-02-1316.html"); 
  server.serveStatic("/d3.min.js", SPIFFS, "/d3.min.js");
  server.serveStatic("/data111.csv", SPIFFS, "/data111.csv");
  server.serveStatic("/data111.json", SPIFFS, "/data111.json");
  server.begin();

}


void loop(void){
  server.handleClient(); 


}

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
//#include <Fonts/FreeSansOblique9pt7b.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <WiFiClientSecure.h>

#include <WebSocketsServer.h>
#include <FS.h> 
#include <XPT2046_Touchscreen.h>

////////////////////////////////////////////////////////////////
#define TIRQ_PIN  2
#define TFT_CS D0  //for D1 mini or TFT I2C Connector Shield (V1.1.0 or later)
#define TFT_DC D8  //for D1 mini or TFT I2C Connector Shield (V1.1.0 or later)
#define TFT_RST -1 //for D1 mini or TFT I2C Connector Shield (V1.1.0 or later)
#define TS_CS D3   //for D1 mini or TFT I2C Connector Shield (V1.1.0 or later)
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
XPT2046_Touchscreen ts(TS_CS);
//////////////////////////////////////////////////////////
int rrrr=0;
//Enter your SSID and PASSWORD
const char* ssid = "NetMASTER Uydunet-E4B0";
const char* password = "mukerremcesur7106";

ESP8266WebServer server (80);
WebSocketsServer webSocket = WebSocketsServer(81);


////////////////////////////
void setup(void){

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN,HIGH);
  //////////////////////////////////////////
  tft.begin();
  tft.setRotation(1);
  tft.setTextWrap(false);//yenibilgi2019-12-11:yazi satiri doldurdugunda asagi gecmesin
  tft.setTextColor(0x0000,0xffff); tft.setTextSize(2);

  tft.fillRect(0,0, 320,120, 0xffff);
  tft.fillRect(0,120,320,240,0xffff );
///////////////////////////////////////////
  ts.begin();
  ts.setRotation(1);
  /////////////////////////////////////////
  //ESP.eraseConfig();//2019-12-19yeni esp zaman zaman wifi server uzerinden gerekli dosyalara tam bağlanamiyordu. bazen iyi bazen kotu idi. belki bu cozum olur.emin degilim
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
     File file7 = SPIFFS.open("/p5.min.js", "r");///deneme
  if(file7){
    Serial.println("p5.min.js acildi");
  }

   
  //WiFi.softAP(ssid, password);
 // IPAddress IP = WiFi.softAPIP();
WiFi.mode(WIFI_STA);
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
Serial.print("Connecting..");
tft.setCursor(10, 10);tft.print("baglaniyor");
delay(1000);
}
tft.setCursor(10, 10);tft.println("baglandi..");
tft.setCursor(10, 50);tft.println(WiFi.localIP());

server.serveStatic("/", SPIFFS, "/index.html"); 
server.serveStatic("/p5.min.js", SPIFFS, "/p5.min.js");
server.begin();
  delay(2000);
  Serial.println("setupbitti");
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);

}
  
void loop(void){

server.handleClient(); 
webSocket.loop();

String xekseni;
String yekseni;
String basinc;

  TS_Point p = ts.getPoint();
  xekseni=String(900*(p.x-300)/3000);
  yekseni=String(600*(p.y-480)/3000);
  basinc =String(p.z/10);
  webSocket.broadcastTXT(xekseni+","+yekseni+","+basinc);
  tft.setCursor(20, 200);tft.print(p.x);


}
void webSocketEvent(byte num, WStype_t type, uint8_t * payload, size_t length)
{
  if(type == WStype_TEXT)
  {
      if (payload[0] == '0')
      {
          digitalWrite(LED_BUILTIN, LOW);
          Serial.println("LED=off");        
      }
      else if (payload[0] == '1')
      {
          digitalWrite(LED_BUILTIN, HIGH);
          Serial.println("LED=on");        
      }
  }
 
  else 
  {
    Serial.print("WStype = ");   Serial.println(type);  
    Serial.print("WS payload = ");
    for(int i = 0; i < length; i++) { Serial.print((char) payload[i]); }
    Serial.println();
 
  }
}

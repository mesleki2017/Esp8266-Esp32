#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

#define TFT_CS D0  //for D1 mini or TFT I2C Connector Shield (V1.1.0 or later)
#define TFT_DC D8  //for D1 mini or TFT I2C Connector Shield (V1.1.0 or later)
#define TFT_RST -1 //for D1 mini or TFT I2C Connector Shield (V1.1.0 or later)
#define TS_CS D3   //for D1 mini or TFT I2C Connector Shield (V1.1.0 or later)

// #define TFT_CS 14  //for D32 Pro
// #define TFT_DC 27  //for D32 Pro
// #define TFT_RST 33 //for D32 Pro
// #define TS_CS  12 //for D32 Pro

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
////////////////////////////////////////
int sayi1;
int sayi2;

void setup() {
  tft.begin();
  tft.setRotation(1); tft.fillScreen(ILI9341_BLUE);
  tft.setTextColor(ILI9341_YELLOW, ILI9341_BLUE); tft.setTextSize(4);//yenibilgi
  tft.setCursor(0, 5); tft.print("Number");


}

void loop() {
  //tft.setTextColor(ILI9341_YELLOW, ILI9341_BLUE); tft.setTextSize(4);//yenibilgi (ILI9341_RED, ILI9341_BLUE) de iki rengi pes pese yazmak
  sayi1 = random(9000); 
  tft.setCursor(10, 50);  tft.print(sayi1);
  //tft.setTextColor(ILI9341_RED, ILI9341_BLUE); tft.setTextSize(4);//yenibilgi
  sayi2 = random(9000); 
  tft.setCursor(10, 100);  tft.print(sayi2);
  delay(100);
}

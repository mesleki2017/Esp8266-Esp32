
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <Wire.h>
#include <VL53L0X.h>

//////////////////////////////////////////////////////////////
VL53L0X sensor;
////////////////////////////////////////////////////////////////
//#define TIRQ_PIN  2
#define TFT_CS D0  //for D1 mini or TFT I2C Connector Shield (V1.1.0 or later)
#define TFT_DC D8  //for D1 mini or TFT I2C Connector Shield (V1.1.0 or later)
#define TFT_RST -1 //for D1 mini or TFT I2C Connector Shield (V1.1.0 or later)
#define TS_CS D3   //for D1 mini or TFT I2C Connector Shield (V1.1.0 or later)
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
//////////////////////////////////////////////////////////

void setup() {
  Serial.begin(115200);
  Wire.begin();
  sensor.setTimeout(500);
  sensor.init();
  sensor.setMeasurementTimingBudget(40000);
  tft.begin();
  tft.setRotation(1);
  tft.setTextWrap(false);//yenibilgi2019-12-11:yazi satiri doldurdugunda asagi gecmesin
  tft.setTextColor(0x0000,0xffff); tft.setTextSize(4);  
  tft.fillRect(0,0, 320,120, 0xffff);
  tft.fillRect(0,120,320,240,0xffff );
 
}

void loop() {
Serial.print("------------"); Serial.println(sensor.RESULT_RANGE_STATUS);
 Serial.println(sensor.readRangeSingleMillimeters());
 tft.setCursor(10, 10);tft.print("            ");tft.setCursor(10, 10);tft.println(sensor.readRangeSingleMillimeters());

}

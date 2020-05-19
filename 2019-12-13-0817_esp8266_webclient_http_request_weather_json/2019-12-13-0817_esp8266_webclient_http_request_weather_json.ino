#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
#define ARDUINOJSON_USE_DOUBLE 1
#include <ArduinoJson.h>
#include <TimeLib.h>
#include <NTPClient.h>
#include <WiFiUdp.h>


#define TFT_CS D0  //for D1 mini or TFT I2C Connector Shield (V1.1.0 or later)
#define TFT_DC D8  //for D1 mini or TFT I2C Connector Shield (V1.1.0 or later)
#define TFT_RST -1 //for D1 mini or TFT I2C Connector Shield (V1.1.0 or later)
#define TS_CS D3   //for D1 mini or TFT I2C Connector Shield (V1.1.0 or later)

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
////////////////////////////////////////
int n=0;// 1 kere kontrolu icin
int i = -600;// kayan altyazi icin
int ii = 0;// kayan yan yazi icin
///////////////////////////////
const char* ssid ="GM 9 Pro";
const char* password ="asdf12345678";
/////////////////////////////////////////
DynamicJsonDocument doc(16000);// openweather dan gelen json bilgisi icin
DynamicJsonDocument doc1(5200);// openexchanges den gelen json bilgisi icin
/////////////////////////////////////////
time_t SuAndakiZaman=0;
time_t DonguSuresiZamanDegiskeni=0;
/////////////////////////////////////////
char *ay[]={"","Ocak ","Subat","Mart ","Nisan","Mayis","Hazrn","Temmz","Agsts","Eylul","Ekim ","Kasim","Aralk"};
//char* gun[]={"","Pzar","Pzrt","Sali","Crsm","Prsm","Cuma","Cmrt"};
//char* gun[]={"","Pazar","Pazartesi","Sali","Carsamba","Persembe","Cuma","Cumartesi"};
/////////////////////////////////////////
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);
/////////////////////////////////////////
void setup()
{
  Serial.begin(115200);
  timeClient.begin();
  tft.begin();
  tft.setRotation(1);
  tft.setTextWrap(false);//yenibilgi2019-12-11:yazi satiri doldurdugunda asagi gecmesin
  tft.setTextColor(0x0000,0xffff); tft.setTextSize(2);
  tft.fillRect(0,0, 320,120, 0xffff);
  tft.fillRect(0,120,320,240,0xffff );
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
  Serial.print("Connecting..");
  tft.setCursor(10, 10);tft.print("baglaniyor");
  delay(1000);
}
tft.setCursor(10, 10);tft.println("baglandi..");
delay(1000);
}

// datazaman ve ApiHavaJsondanZamanBilgisi bibirinin opsiyonu. doc["list"][i]["dt_txt"] den zaman bilgisi text olarak aliniyor.doc["list"][i]["dt"] den
//ise zaman bilgisi saniye fotmatinda aliniyor
//int datazaman(int i){//yeni bilgi int tipi fonksiyon da return asagidaki gibi olabiliyor
//  char zamantext[15];
//  serializeJson(doc["list"][i]["dt_txt"], zamantext);//datazaman json dan zamanı butun text olarak aliyor
//  tft.setTextColor(0x6043,0x6d56);
//  return tft.print(zamantext);
// }
 
int ApiHavaJsondanZamanBilgisi(int i){//yeni bilgi int tipi fonksiyon da return asagidaki gibi olabiliyor. int tipi fonksiyonlari ilk defa bu
  //programda kullandim. 
  String zaman;
  time_t t1=0;
  String text1="";
  serializeJson(doc["list"][i]["dt"], zaman);//ApiHavaJsondanZamanBilgisi json dan zamanı saniye formatinda aliyor
  t1=zaman.toInt();
  tft.setTextColor(0x6043,0x6d56);
  text1=String(day(t1))+ String("-")+ay[month(t1)]+ String(" ");
  if (hour(t1) < 10)text1=text1+String("0");
  text1=text1+String(hour(t1))+ String(":");
  return tft.print(text1);
 }
/////////////////////////////////////////////////////////////////////////////////////////////////////
int ApiHavaJsondanSicaklikveDurumBilgisi(int i){//yenibilgi int tipi fonksiyon da return asagidaki gibi olabiliyor
  String sicaklikDerece="";
  sicaklikDerece=JsonDanSicaklikAl(i);
  int sicaklikInt=sicaklikDerece.toInt();// sicakligi string den int cevirip sicakliga gore metintaban rengini degistirmek istiyorum
  int havaSicaklikRengi;
  if (   16>=sicaklikInt && 12 <sicaklikInt){havaSicaklikRengi=0xed4b;}
  if (   12>=sicaklikInt && 8 <sicaklikInt){havaSicaklikRengi=0xed63;}
  if (   8>=sicaklikInt && 4 <sicaklikInt){havaSicaklikRengi=0xedc3;}
  if (   4>=sicaklikInt && 0 <sicaklikInt){havaSicaklikRengi=0xdec3;}
  if (   0>=sicaklikInt && -2 <sicaklikInt){havaSicaklikRengi=0x6c56;}
  if (  -2>=sicaklikInt && -4 <sicaklikInt){havaSicaklikRengi=0x6cf6;}
  if (  -4>=sicaklikInt && -6 <sicaklikInt){havaSicaklikRengi=0x6d56;;}
  return LcdYeSicaklikBilgisiYaz(sicaklikInt,JsonDanYagisDurumAl(i),havaSicaklikRengi);
 }
//yenibilgi https://chrishewett.com/blog/true-rgb565-colour-picker/
////////////////////////////////////////////////////////////////////////////////////////////////
int LcdYeSicaklikBilgisiYaz(int sicaklik,String durum,int renk){
  tft.setTextColor(0x6043,renk);tft.print(String(sicaklik));tft.print(" ");tft.setTextColor(0xf177,renk);tft.print(durum);if(durum.length()==4){tft.print("  ");};if(durum.length()==5){tft.print(" ");};
}
/////////////////////////////////////////////////////////////////////////////////////////////
String JsonDanYagisDurumAl(int i){//yenibilgi fonksiyonu string return lu tanimlamak
  String c="";
  serializeJson(doc["list"][i]["weather"][0]["main"], c);
  c.replace("\"","");//yenibilgi2019-12 : https://stackoverflow.com/questions/32414079/android-how-to-remove-character-from-string
  return c ;
}
//////////////////////////////////////////////////////////////////////////////////////////
String JsonDanSicaklikAl(int i){//yenibilgi fonksiyonu string return lu tanimlamak
  String b="";
  serializeJson(doc["list"][i]["main"]["temp"], b);
  int s=b.toInt();
  return String(s) ;
}
////////////////////////////////////////////////////////////////////////////////////////// 
 int JsonDanAltinAl(){
  String text2="";
  serializeJson(doc1["rates"]["XAU"], text2);
  float v=text2.toFloat();
  return (1/v); // return int olarak yapar
 }
////////////////////////////////////////////////////////////////////////////////////////
 float JsonDanDolarAl(){
  String text2="";
  serializeJson(doc1["rates"]["TRY"], text2);
  float v=text2.toFloat();
  return v;// return u float olarak yapar
 }
/////////////////////////////////////////////////////////////////////////////////////////////
int LcdYeHavaBilgisiYaz(int satiraralik){
  if(n==0){//ekrana 1 kere yazdirilsin 
    tft.setTextSize(2);//yenibilgi https://forum.arduino.cc/index.php?topic=364055.0
    tft.setCursor(0,0);tft.setTextColor(0xf2d0,0x84f0);tft.print(" Tarih  Saat C Hava  ");
    tft.setCursor(0,satiraralik*1);ApiHavaJsondanZamanBilgisi(2);tft.setTextColor(0x6043,0xffff);tft.print(" ");ApiHavaJsondanSicaklikveDurumBilgisi(2);
    tft.setCursor(0,satiraralik*2);ApiHavaJsondanZamanBilgisi(3);tft.setTextColor(0x6043,0xffff);tft.print(" ");ApiHavaJsondanSicaklikveDurumBilgisi(3);
    tft.setCursor(0,satiraralik*3);ApiHavaJsondanZamanBilgisi(4);tft.setTextColor(0x6043,0xffff);tft.print(" ");ApiHavaJsondanSicaklikveDurumBilgisi(4);
    tft.setCursor(0,satiraralik*4);ApiHavaJsondanZamanBilgisi(5);tft.setTextColor(0x6043,0xffff);tft.print(" ");ApiHavaJsondanSicaklikveDurumBilgisi(5);
    tft.setCursor(0,satiraralik*5);ApiHavaJsondanZamanBilgisi(6);tft.setTextColor(0x6043,0xffff);tft.print(" ");ApiHavaJsondanSicaklikveDurumBilgisi(6);
    tft.setCursor(0,satiraralik*6);ApiHavaJsondanZamanBilgisi(7);tft.setTextColor(0x6043,0xffff);tft.print(" ");ApiHavaJsondanSicaklikveDurumBilgisi(7);
    tft.setCursor(0,satiraralik*7);ApiHavaJsondanZamanBilgisi(8);tft.setTextColor(0x6043,0xffff);tft.print(" ");ApiHavaJsondanSicaklikveDurumBilgisi(8);
    tft.setCursor(0,satiraralik*8);ApiHavaJsondanZamanBilgisi(9);tft.setTextColor(0x6043,0xffff);tft.print(" ");ApiHavaJsondanSicaklikveDurumBilgisi(9);
    tft.setCursor(0,satiraralik*9);ApiHavaJsondanZamanBilgisi(10);tft.setTextColor(0x6043,0xffff);tft.print(" ");ApiHavaJsondanSicaklikveDurumBilgisi(10);
    tft.setCursor(0,satiraralik*10);ApiHavaJsondanZamanBilgisi(11);tft.setTextColor(0x6043,0xffff);tft.print(" ");ApiHavaJsondanSicaklikveDurumBilgisi(11);
    tft.setCursor(0,satiraralik*11);ApiHavaJsondanZamanBilgisi(12);tft.setTextColor(0x6043,0xffff);tft.print(" ");ApiHavaJsondanSicaklikveDurumBilgisi(12);
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////
int LcdYeAltYaziKurBigisi(int satiraralik,int satir){
  SuAndakiZaman=now();
  tft.setTextColor(0x000,0x17e9); tft.setTextSize(4);
  if ( i< 240){//kayan yazi icin
    tft.setCursor(i,satiraralik*satir);tft.print(" Dolar=");tft.print(JsonDanDolarAl());tft.print(" AltinOns=");tft.print(JsonDanAltinAl());
    tft.setTextColor(0x0000, 0x17e9); tft.setTextSize(4);
    tft.print("|SAAT ");if (hour(SuAndakiZaman) < 10)tft.print("0");tft.print(hour(SuAndakiZaman));tft.print(":");if (minute(SuAndakiZaman) < 10)tft.print("0");tft.print(minute(SuAndakiZaman));
    i=i+1;
  }else{
    tft.setTextColor(0x0000, 0x17e9);
    tft.setCursor(0,satiraralik*satir);tft.print("              ");
    i=-600;
  }
  yanKayanYazi(JsonDanSicaklikAl(1));
}
///////////////////////////////////////////////////////////////////////////////////////////////
int yanKayanYazi(String yazi){
  if ( ii< 175){
    tft.setTextSize(4);
    tft.setTextColor(0x0000, 0x3f3b);
    tft.setTextColor(0xa09f, 0x3f3b);tft.setCursor(254,ii-1);tft.print("    ");tft.setCursor(254,ii);tft.print("");tft.print(yazi);ii=ii+1;
  }
  else
    {tft.setCursor(254,0);ii=0;tft.setTextColor(0x0000,0x3f3b);}
}
//////////////////////////////////////////////////////////////////////////////////////////////
int internetZamanSunucusu(){
  timeClient.update();
  timeClient.setTimeOffset(3600+3600+3600);// saat farki icin
  SuAndakiZaman = timeClient.getEpochTime();
  setTime(SuAndakiZaman);
}
////////////////////////////////////////////////////////////////////////////////////////////
int ApidenDataCekmeDonguSuresi(int saniye){// belirlenen saniyede bir eger wifi bagli ise yani "3" ise ve n de 1 ise n=0 yapar ve json lari temizler
  //n=0 ise loop ta apilere baglanip data istenir
  SuAndakiZaman=now();
  if((SuAndakiZaman-DonguSuresiZamanDegiskeni)>=saniye){
   if ((WiFi.status() == 3)&& n== 1){
      n=0; doc.clear(); doc1.clear();tft.fillRect(0,0, 320,240, 0xffff);}
   DonguSuresiZamanDegiskeni=SuAndakiZaman;
  }
}
////////////////////////////////////////////////////////////////////////////////////////
void loop()
{
ApidenDataCekmeDonguSuresi(3600);//3600 saniye yani bir saat te bir n i 0 yapar,ve json doc ları temizler

if ((WiFi.status() == WL_CONNECTED)&& n==0) { // wifi bagli ise ve n ==0 ise. n kontrolu sadece 1  kere data alsin diye.
  /////////////////////////////////////////////////////////////////////////////////
  internetZamanSunucusu();// bunun hava veya kur bilgisi ile hic alakasi yok. sadece o anki saat bilgisini aliyor
  /////////////////////////////////////////////////////////////////////////////////
  HTTPClient httpHava;  //hava bilgisini almak icin http objesi olusturdum
  httpHava.begin("http://api.openweathermap.org/data/2.5/forecast?lat=39.966477&lon=32.879326&APPID=3d183cadc635fb5328f1eb40606ae0df&units=metric");  //Specify request destination
  int httpDenetleHava = httpHava.GET();   //Send the request
  if (httpDenetleHava == 200 ) { //Check the returning code
    deserializeJson(doc,httpHava.getString());//yenibilgi2019-13 :http.getString i dogrudan deserializeJson icinde kullanmak. daha gecici bir strin alani kullaniyordum arada.bu tarzda degerler stringe bazen yukluyor bazen yuklemiyor.https://github.com/esp8266/Arduino/issues/4951
    delay(100);
    ///////////////////////////////////////////////
    LcdYeHavaBilgisiYaz(17);// lcd de gosterme kismi.bunu sadece belirli surede 1 kere calistiriyorum cunku hava bilgisi surekli degismiyor
    //LcdYeHavaBilgisiYaz yi alyazitftf2 nin yanina da koysam olur ama sistem yavasliyor bu sefer  
      }
  httpHava.end(); 
//////////////////////////////////////////////////////////////////////////////////
  HTTPClient httpAltinKur; // altin bilgisini almak icin httpclient objesi olusturdum.
  httpAltinKur.begin("http://openexchangerates.org/api/latest.json?app_id=e4e7bd163f154335aa60224d0fc2ae01");  //Specify request destination
  int httpDenetleAltinKur = httpAltinKur.GET(); 
  if (httpDenetleAltinKur == 200) {
    deserializeJson(doc1,httpAltinKur.getString());
    delay(100);
    }
  httpAltinKur.end();
//////////////////////////////////////////////////////////////////////////////////
  n=n+1; 
}// wifi status ve n==0 , if kontrolunun sonu
///////////////////////////////////////////////////////////////////////////////
LcdYeAltYaziKurBigisi(17,12);


}




#include <ArduinoJson.h>

unsigned long zaman1=0;
unsigned long k=0;



void setup(void){
Serial.begin(115200);
DynamicJsonDocument doc1(1024);
JsonArray renk = doc1.createNestedArray("renk");
JsonArray sayi = doc1.createNestedArray("sayi");
renk.add("mavi");
renk.add("beyaz");

sayi.add("bir");
sayi.add(2);

char a[60];
serializeJson(doc1, Serial);
serializeJson(doc1, a);Serial.println("");
Serial.println(a);





}


void dataekle(){
  unsigned long zaman2 = millis();
  if ( zaman2 - zaman1 > 500 ) {
    zaman1=zaman2;
    k=(k+1);
}  
  }
  




void loop(void){

 //dataekle();


}

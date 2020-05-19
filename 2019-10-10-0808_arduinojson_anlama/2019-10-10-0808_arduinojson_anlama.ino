


#include <ArduinoJson.h>

unsigned long zaman1=0;
unsigned long w=0;



void setup(void){
Serial.begin(115200);

}

/////////////////////////doc199//////////////////////////////////////////////////////
// bu bolumu setup icinde tanimlayamiyorum///////////////////////////////////////////
DynamicJsonDocument doc199(400);
JsonArray zaman199 = doc199.createNestedArray("zaman199");
JsonArray sayi199 = doc199.createNestedArray("sayi199");
////////////////////////////////////////////////////////////////////////////////

void dataekle(){
  unsigned long zaman2 = millis();
  if ( zaman2 - zaman1 > 500 ) {//500ms de bir data ekleme icin
    zaman1=zaman2;
    
   if ( w < 10){   
    zaman199.add(zaman1);
    sayi199.add(w);
    int k199= sayi199[w];// int , string olup olmadigi onemli
    serializeJson(doc199, Serial);Serial.println("");
    Serial.println("--------");
    Serial.print("k199 ==== ");Serial.println(k199);
    Serial.println("--------");
    Serial.print("doc199.size() ==== ");Serial.println(doc199.size());
    Serial.println("--------");
    Serial.print("zaman199.size() ==== ");Serial.println(zaman199.size());
    Serial.println("--------");
    Serial.print("sayi199.size() ==== ");Serial.println(sayi199.size());
    Serial.println("--------");
    Serial.print("doc199.memoryUsage() ==== ");Serial.println(doc199.memoryUsage());
    Serial.println("--------");
    w=(w+1);
      }
      } 
  if ( w== 10) {
    //program surekli aynı isi yapmasın diye gorsel amaclı anlamak icin bir if dongusu
    dataset();
    w=w+1;
 }
     if ( w== 11) {
      // remove komutu datayi siliyor ancak hafiza kullanimi "memoryUsage" ayni kaliyor
       datasilekle();  
       w=w+1; 
     }
if ( w== 112) {
  
  
  w=w+1; 
  
}
     
  }

  void dataset(){
    Serial.println("---------------------------------------------------------------");
    Serial.println("---------------------------------------------------------------");
    Serial.println("---------------------------------------------------------------");
    Serial.println("---------------Data yı  0 a set ettim--------------------------");
    sayi199[0]=0;sayi199[1]=0;sayi199[2]=0;sayi199[3]=0;sayi199[4]=0;sayi199[5]=0;sayi199[6]=0;sayi199[7]=0;sayi199[8]=0;sayi199[9]=0;
    serializeJson(doc199, Serial);Serial.println("");
    Serial.print("doc199.memoryUsage() ==== ");Serial.println(doc199.memoryUsage());

      }
void datasilremoveekleadd(){
    Serial.println("---------------------------------------------------------------");
    Serial.println("---------------------------------------------------------------");
    Serial.println("------- remove la zamam199 in butun elemanlarini sildim--------");
  
    //zaman199.remove(0);zaman199.remove(1);zaman199.remove(2);zaman199.remove(3);zaman199.remove(4);//bu ise yaramiyor
    zaman199.remove(0);zaman199.remove(0);zaman199.remove(0);zaman199.remove(0);zaman199.remove(0);
    zaman199.remove(0);zaman199.remove(0);zaman199.remove(0);zaman199.remove(0);zaman199.remove(0);
    // pespese remove(0) kullanilmasi sebebi 0 ci eleman silinince ondan sonraki eleman artik 0 ci eleman olmus oluyor
    Serial.print("zaman199.size() ==== ");Serial.println(zaman199.size());
    serializeJson(doc199, Serial);Serial.println("");
    Serial.print("doc199.memoryUsage() ==== ");Serial.println(doc199.memoryUsage());
    
    Serial.println("--------------------remove yaptiktan sonra add ile--------------");
    Serial.println("---------------------eleman eklersem memory usage ne olur-------");
    zaman199.add(8888);// rasgele bir deger
    serializeJson(doc199, Serial);Serial.println("");
    Serial.print("doc199.memoryUsage() ==== ");Serial.println(doc199.memoryUsage());
    Serial.println("---------------------------------------------------------------");
    Serial.println("Sonuc : bir çok elemani remove silip tekrar add ile sona baska bir eleman eklemek");
    Serial.println("MemoryUsage arttiriyor.");

  
}

void datasilekle(){
  Serial.println("---------------------------------------------------------------");
  Serial.println("---------------------------------------------------------------"); 
  Serial.print("zaman199.size() ==== ");Serial.println(zaman199.size());Serial.print("sayi199.size() ==== ");Serial.println(sayi199.size());
  zaman199.remove(0);sayi199.remove(0);
  Serial.print("zaman199.size() ==== ");Serial.println(zaman199.size());Serial.print("sayi199.size() ==== ");Serial.println(sayi199.size());
  sayi199[9]=999;zaman199[9]=999;
  serializeJson(doc199, Serial);Serial.println("");
  Serial.print("doc199.memoryUsage() ==== ");Serial.println(doc199.memoryUsage());
  
}
  
void loop(void){

 dataekle();


}

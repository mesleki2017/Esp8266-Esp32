


#include <ArduinoJson.h>

unsigned long zaman1=0;
unsigned long w=0;



void setup(void){
Serial.begin(115200);

//StaticJsonDocument<200> doc1;
DynamicJsonDocument doc1(200);
JsonArray array33 = doc1.to<JsonArray>();
JsonArray renk = array33.createNestedArray();
JsonArray sayi = array33.createNestedArray();
renk.add("mavi");
renk.add("kirmizi");
sayi.add(1);
sayi.add(44);
sayi.add(100);

char a[40];
char b[40];
serializeJson(doc1, Serial);Serial.println("");
serializeJson(doc1[0][1], Serial);Serial.println("");
serializeJson(doc1[0][0], a);
Serial.print("a=");Serial.println(a);
serializeJson(doc1[1][0], b);
Serial.print("b=");Serial.println(b);
Serial.println(int(b)*2);
Serial.println("-------------------doc555---------------------------------------");
DynamicJsonDocument doc555(200);
doc555["sayi"] = 42;
doc555["sayi"] = 62;
doc555.add(100);
serializeJson(doc555, Serial);Serial.println("");
Serial.println("--------------------doc666--------------------------------------");
DynamicJsonDocument doc666(200);
doc666.add(42);
doc666.add(62);
serializeJson(doc666, Serial);Serial.println("");
Serial.println("--------");
JsonArray isim = doc666.createNestedArray("isim");
isim.add("ali");//!!!!!!!!!!!!!!!!!!!!!!!!!
serializeJson(doc666, Serial);Serial.println("");
Serial.println("-------------------doc888--Object-------------------------------------");
DynamicJsonDocument doc888(200);
JsonObject isim3 = doc888.to<JsonObject>();
isim3["aaaa"]="bbb";
JsonArray sayi3 = isim3.createNestedArray("sayi3");
sayi3.add(42);
sayi3.add(62);
serializeJson(doc888, Serial);Serial.println("");
Serial.println("------");
int h=isim3["sayi3"][0];
Serial.println(h);
Serial.println(h*7);
//Serial.println(isim3["sayi3"][0]);// HATA Veriyor !!!!!!!!!!!!!!!!!!!!!!!
String y=isim3["aaaa"];//String yerine Char yazinca olmuyor!!!!!!!!!!!!!
Serial.println(y);
Serial.println("-------------------doc777---Array------------------------------------");
DynamicJsonDocument doc777(200);
JsonArray isim2 = doc777.createNestedArray("isim2");
isim2.add("ali");
isim2.add("veli");
doc777.add(42);// bu satiri Eklemiyor !!!!!!!!!!!
doc777.add(62);// bu satiri Eklemiyor !!!!!!!!!!!
serializeJson(doc777, Serial);Serial.println("");

Serial.println("--------------------doc999----Array----------------------------------");
DynamicJsonDocument doc999(200);
JsonArray isim4 = doc999.createNestedArray("isim4");
JsonArray sayi4 = doc999.createNestedArray("sayi4");
isim4.add("ali");
isim4.add("veli");
sayi4.add(99);
sayi4.add(77);
serializeJson(doc999, Serial);Serial.println("");
Serial.println("--------");
String h999=isim4[0];
Serial.println(h999);
Serial.println("--------");
int k999= sayi4[0];
Serial.println(k999);
Serial.println(k999*2);
Serial.println("--------------------doc199--------------------------------------");


Serial.println("--------------------SetupSON--------------------------------------");
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
       datasil();  
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
void datasil(){
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
  
void loop(void){

 //dataekle();


}

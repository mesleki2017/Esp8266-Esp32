const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="tr">


<style>
body {
  font-family: Arial;
  margin: 0;
}

.flex-container {
  display: -webkit-flex;
  display: flex;
  -webkit-flex-direction: column;
  flex-direction: column;
  width: 400px;
  height: 250px;
  background-color: lightgrey;
}

.flex-item {
  background-color: cornflowerblue;
  display: -webkit-flex;
  display: flex;
  width: 200px;
  height: 200px;
  margin: 10px;
}

.grid-container {
  display: grid;
  grid-template-columns: auto auto ;
  background-color: #2196F3;
  padding: 10px;
}
.grid-item {
  background-color: rgba(255, 255, 255, 0.8);
  border: 1px solid rgba(0, 0, 0, 0.8);
  padding: 20px;
  font-size: 30px;
  text-align: center;
}




.stildeneme{ 
  background-color: #52BE80; /* Green */
  width: 45%;
  height: 20% ;
  border: none;
  color: black;
  text-align: center;
  text-decoration: none;
  font-size: 16px;
  font-weight: bold;
 
}

.stildeneme1 {
  background-color: #FAFA00; /* Green */
  width: 45%;
  height: 40% ;
  border: none;
  color: black;
  text-align: center;
  text-decoration: none;
  font-size: 16px;
  font-weight: bold;
  
}

.stildeneme2 {
  background-color: #C39BD3  ; /* Green */
  margin: auto;
  width: 45%;
  height: 20% ;
  border: none;
  color: black;
  text-align: center;
  text-decoration: none;
  font-size: 16px;
  font-weight: bold;
  
}
.stildeneme3 {
  background-color: #F1C40F  ; /* Green */
  width: 45%;
  height: 20% ;
  border: none;
  color: black;
  text-align: center;
  text-decoration: none;
  font-size: 16px;
  font-weight: bold;
  
}
.button {
  background-color: #4CAF50; /* Green */
  border: none;
  color: white;
  padding: 20px;
  text-align: center;
  text-decoration: none;
  display: inline-block;
  font-size: 16px;
  margin: 4px 2px;
  cursor: pointer;
}
.button1 {border-radius: 2px;}
.button2 {border-radius: 4px;}
.button3 {border-radius: 8px;}
.button4 {border-radius: 12px;}
.button5 {border-radius: 50%;}
</style>



<body>
  
  
<div class="grid-container">

  <div class="grid-item">
  <p>Sicaklik</p><br> 
  </div>
  
  <div class="grid-item">
  <p> <span id="analog0">0</span></p><br>
  
  </div> 
  

  <div class="grid-item">
  <button class="button button1" onclick="sendData(1)" style="background-color: blue; font-size : 20px;font-weight: bold;width: 40%; height: 80% ;">LED ON</button>
  <button class="button button5" onclick="sendData(0)" style="background-color: red;font-size : 20px;font-weight: bold;width: 40%; height: 40% ;">LED OFF</button><BR>
  </div>

<div class="grid-item">
  <p>5. cikis durumu : <span id="LEDState">NA</span></p><br> 
</div>



</div>



 


<script>
// program kismi iki script arasinda kalan yere yaziliyor
  
  


function sendData(led) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
                                          if (this.readyState == 4 && this.status == 200) {
                                          document.getElementById("LEDState").innerHTML =this.responseText;
                                                                                          }
                                         };
  xhttp.open("GET", "setLED?LEDstate="+led, true);
  xhttp.send();
                        }

//Analog ve timer degeri almak icin
 getData("readADC00","analog0");
 getData("readX","Xoku");

function getData(okunacak,yazilacak) {
  var xhttp1 = new XMLHttpRequest();
  xhttp1.onreadystatechange = function() {
                                          if (this.readyState == 4 && this.status == 200) {
                                          document.getElementById(yazilacak).innerHTML =this.responseText;
                                                                                          }
                                          };
 setInterval(aldata,500);
  function aldata(){
    xhttp1.open("GET", okunacak, true);
    xhttp1.send();
                    }
                    }


</script>


<br><br><a href="https://s7otomasyon.com">s7otomasyon.com</a>
</body>
</html>
)=====";

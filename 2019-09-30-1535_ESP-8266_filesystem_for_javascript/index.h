const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="tr">

<script src = "\Chart.min.js"></script>
<style>
body {
  font-family: Arial;
  margin: 0;
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

</style>



<body>
    <div class="chart-container" position: relative; height:350px; width:100%">
        <canvas id="Chart" width="400" height="400"></canvas>
    </div> 
  
<div class="grid-container">


  <div class="grid-item">
  <p> <span id="analog0">0</span></p><br>
  
  </div> 
  
</div>

<script>
var values = [50,8,3];
var timeStamp = [1,2,3];
function showGraph()
{
    for (i = 0; i < arguments.length; i++) {
      values.push(arguments[i]);    
    }
 
    var ctx = document.getElementById("Chart").getContext('2d');
    var Chart2 = new Chart(ctx, {
        type: 'line',
        data: {
            labels: timeStamp,  //Bottom Labeling
            datasets: [{
                data: values,
            }],
        },

    });
 
}
//window.onload = function() {
//  console.log(new Date().toLocaleTimeString());
//  showGraph(5,10,4,58);
//};


 getData("readADC00","analog0");


function getData(okunacak,yazilacak) {
  var xhttp1 = new XMLHttpRequest();
  xhttp1.onreadystatechange = function() {
                                          if (this.readyState == 4 && this.status == 200) {

                                          document.getElementById(yazilacak).innerHTML =this.responseText;
                                          var ADCValue = this.responseText;
                                          values.push(ADCValue);
                                          timeStamp.push(ADCValue);
                                          showGraph();
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

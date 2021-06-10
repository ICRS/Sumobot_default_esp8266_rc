const char CONTROL_1[] PROGMEM = R"=====(<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, user-scalable=no">
<style>

.slider {
  -webkit-transform: rotate(-90deg);
  margin: 50% 0% 50% 0%;

}

.center {
  display: flex;
  justify-content: center;
  align-items: center;
  height: 100%;
  top: 100px;
}

</style>
</head>
<body>
<div class="center">
<input type="range" min="-5" max="5" value="0" class="slider" list="ticks" id="left">  
<input type="range" min="-5" max="5" value="0" class="slider" list="ticks" id="right">
</div>

<datalist id="ticks">
    <option>-5</option>
    <option>0</option>
    <option>5</option>
</datalist>
</body>

<script>

  var Socket = new WebSocket('ws://' + window.location.hostname + ':81/');
  Socket.onopen = function(){ 
  Socket.send("Connect ");
  }
  Socket.onmessage = function(e){
  console.log(e.data);}
  function send(x, y){
    Socket.send("l" + x +"r" +y);
  }
  
  var sliderLeft = document.getElementById("left");
  var sliderRight = document.getElementById("right");
  
  sliderLeft.onchange=function(){send(sliderLeft.value,sliderRight.value);}
  sliderRight.onchange=function(){send(sliderLeft.value,sliderRight.value);}
  

  </script>
</html>
)=====";

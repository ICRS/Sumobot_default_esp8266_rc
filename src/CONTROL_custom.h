const char CONTROL_custom[] PROGMEM = R"=====(<!DOCTYPE html>
<html>
 <head>
    <title>Custom Controls</title>
    <style>
      p {
        text-align: center;
      }
    </style>
  </head>
  <body>
  </body>

  <script> 

  var socket = new WebSocket('ws://' + window.location.hostname + ':81/');
  socket.onopen = function(){ 
    socket.send("Connect ");
  }
  
  socket.onmessage = function(e){
  console.log(e.data);}
      
  function SendUrl(x, y){
    console.log(x);
    console.log(y);
    socket.send("l" + x + "r" +y);
  }
  
  document.onkeydown = checkKey;
  document.onkeyup = function() {SendUrl(0,0)};

  function checkKey(e) {

    e = e || window.event;

    if (e.keyCode == '38') {
        // up arrow
        SendUrl(3,3);
    }
    else if (e.keyCode == '40') {
        // down arrow
        SendUrl(-3,-3);
    }
    else if (e.keyCode == '37') {
       // left arrow
       SendUrl(-3,3);
    }
    else if (e.keyCode == '39') {
       // right arrow
       SendUrl(3,-3);
    }

}

  
  </script>
</html>
)=====";

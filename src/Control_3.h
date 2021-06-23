const char CONTROL_3[] PROGMEM = R"=====(<!DOCTYPE html>
<html>
 <style>
      button {
          border: none;
          color: white;
          padding: 15px 32px;
          text-align: center;
          text-decoration: none;
          display: inline;
          font-size: 24px;
          margin: 4px 2px;
          cursor: pointer;
          background-color: #4CAF50;
      }
      .center {
          align-items: center;
          display: flex;
          justify-content: center;
      }
    p {text-align: center;}
  </style>
  <head>
      <meta charset="utf-8" />
      <title>RC car</title>
      <script>
        function send(valueL, valueR){
        var url = "/0?l=" + valueL + "&r="+ valueR;
        fetch(url);
        console.log("SEND");
        console.log(valueL);
        console.log(valueR);
      }
      </script>
  </head>
  <body>
    <div id="wrapper"></div>
    <div class="center">
      <h1> <!-- Version 1.0 --> </h1>
    </div>
    <div class="center">
      <pre><button type="button" id="Forward_L">&#8662</button>  <button type="button" id="forward">&#8679</button><img >  <button type="button" id="Forward_R">&#8663</button></pre>
    </div>
    <p></p>
    <div class="center">  
        <pre><button type="button" id="left">&#8678</button>        <button type="button" id="right">&#8680</button></pre>
    </div>
    <p></p>
    <div class="center">
      <button type="button" id="back">&#8681</button>
    </div>
    <script>
      conlog(left);
      conlog(forward);
      conlog(right);
      conlog(back);
      conlog(Forward_R);
      conlog(Forward_L);
      /*
        Forward_R
        Forward_L
      */
      var socket = new WebSocket('ws://' + window.location.hostname + ':81/');
      socket.onopen = function(){ 
        socket.send("Connect ");
      }
      
      socket.onmessage = function(e){
        console.log(e.data);}

      function send(x,y) {
        socket.send("l" + x +"r" +y);
      }
        
      function conlog(direction){
        direction.onmouseup = function(){
            send(0,0);
          }
      }
      left.onmousedown = function(){
          send(-5,5)
        }
      forward.onmousedown = function(){
          send(5,5);
        }
      back.onmousedown = function(){
          send(-5,-5);
        }
      Forward_R.onmousedown = function(){
          send(5,2);
        }
      right.onmousedown = function(){
          send(5,-5);
        }
      Forward_L.onmousedown = function(){
          send(2,5)
        }
      var leftTouchObj = document.getElementById('left');
      leftTouchObj.addEventListener("touchstart", function(event) { send(5, 2); });
      leftTouchObj.addEventListener("touchend", function(event) { send(0, 0); send(0, 0);});
      var forwardTouchObj = document.getElementById('forward');
      forwardTouchObj.addEventListener("touchstart", function(event) { send(5, 5); });
      forwardTouchObj.addEventListener("touchend", function(event) { send(0, 0); send(0, 0);});
      var backTouchObj = document.getElementById('back');
      backTouchObj.addEventListener("touchstart", function(event) { send(-5, -5); });
      backTouchObj.addEventListener("touchend", function(event) { send(0, 0); send(0, 0);});
      var Forward_RTouchObj = document.getElementById('Forward_R');
      Forward_RTouchObj.addEventListener("touchstart", function(event) { send(5, -5); });
      Forward_RTouchObj.addEventListener("touchend", function(event) { send(0, 0); send(0, 0);});
      var rightTouchObj = document.getElementById('right');
      rightTouchObj.addEventListener("touchstart", function(event) { send(2, 5); });
      rightTouchObj.addEventListener("touchend", function(event) { send(0, 0); send(0, 0);});
      var Forward_LTouchObj = document.getElementById('Forward_L');
      Forward_LTouchObj.addEventListener("touchstart", function(event) { send(-5, 5); });
      Forward_LTouchObj.addEventListener("touchend", function(event) { send(0, 0); send(0, 0);});
      
      document.addEventListener("contextmenu", function (e) { e.preventDefault(); }, false);
</script>
</body>
</html>
)=====";

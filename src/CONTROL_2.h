const char CONTROL_2[] PROGMEM = R"=====(<!DOCTYPE html>

<html lang="en" xmlns="http://www.w3.org/1999/xhtml">



    <head>
        <meta charset="utf-8" />
        <title></title>
        <meta name="viewport" content="width=600, initial-scale=1.0, user-scalable=yes">
        
        <style>
            #drag {
                position: absolute;
            }

            #fix {
                position: fixed;
            }

        </style>

    </head>

    <body>


        <div>
          
            <div id="fix" >
              <svg height="500" width="500">
                <circle cx="250" cy="250" r="250" fill="rgb(230,230,230)" stroke="black" stroke-width="1" id="circle2"/>
                Sorry, your browser does not support inline SVG.  
              </svg> 
          </div>


          <div id="drag">
            <svg height="100" width="100">
              <circle cx="50" cy="50" r="49" fill="white" stroke="black" stroke-width="2" />
              Sorry, your browser does not support inline SVG.  
            </svg>
          </div>

        </div>


    </body>


    <script>

        var socket = new WebSocket('ws://' + window.location.hostname + ':81/');
        socket.onopen = function(){ 
          socket.send("Connect ");
        }
  
        socket.onmessage = function(e){
        console.log(e.data);}
        
        function SendUrl(x, y){
          socket.send("l" + x +"r" +y);
        }
  
        var leftval = window.innerWidth/ 2 -50    , topval = window.innerHeight/ 2 -100;
        console.log(leftval);

        document.getElementById("drag").style.top = topval +"px";
        document.getElementById("drag").style.left = leftval + "px";

        document.getElementById("fix").style.top = topval - 200 + "px";
        document.getElementById("fix").style.left = leftval - 200 + "px";

        var L = 0, R = 0;

        dragElement(document.getElementById("drag"));
        
      function dragElement(elmnt) {
        var pos3 = 0, pos4 = 0, mag =0, send;
         
            /* otherwise, move the DIV from anywhere inside the DIV:*/
            elmnt.ontouchstart = dragMouseDown;
            elmnt.onmousedown = dragMouseDown;
            
            
            function dragMouseDown(e) {

                send = setInterval(function () { SendUrl(L, R); }, 500);
                document.ontouchmove = elementDragTouch;
                document.ontouchend = closeDragElement;
          // call a function whenever the cursor moves:
                document.onmousemove = elementDrag;
                document.onmouseup = closeDragElement;
                

                
        }

        function elementDrag(e) {
          e = e || window.event;
          e.preventDefault();
          // calculate the cursor position:
          pos3 = e.clientX;
                pos4 = e.clientY;
                
                mag = Math.sqrt((pos3 - (50+leftval)) ** 2 + (pos4 - (50+topval)) ** 2) //determine distance from centre mouse is at
                //Note!!! 250,250 is centre of circle 
          
          var multiplier = 0;  //This determines the power to each motor, 5 is full power
          var angle = Math.atan2((pos3-(50+leftval)),(pos4-(50+topval))); //This is used to determine the motor's individual power for turning/direction

                // If mouse goes outside circle set maximum distance circle can move
                if (mag > 200) {
                    // set the joystick's new position (inside cirle but mouse outside circle):
                    // 200 is the radius of outer circle
                    elmnt.style.top = topval + (pos4 - (50 + topval)) * (200 / mag) + "px";
                    elmnt.style.left = leftval + (pos3 - (50 + leftval)) * (200 / mag) + "px"; 
          }

          else{
                    // set the joystick's new position:
                    elmnt.style.top = (pos4 - 50) + "px";
            elmnt.style.left = (pos3- 50) + "px"; //elmnt.offsetLeft - pos1
          }

                //Setting  multiplier by determining range in which magnitude is located
          if(0<mag && mag<50){
            multiplier = 0;
          }

          if(50<mag && mag<100){
            multiplier = 1;
          }

          if(100<mag && mag<150){
            multiplier = 3;
          }

          if(150<mag){
            multiplier = 5;
          }
          
          if(-(Math.PI/8)<angle && angle<(Math.PI/8)){
                    // Sector 5
                    L = -5;
                    R = -5;
          }
          
          if(-3*(Math.PI/8)<angle && angle< -(Math.PI/8)){
                    // Sector 6
                    L = -5;
                    R = 0;
          }

          if(-5*(Math.PI/8)<angle && angle< -3*(Math.PI/8)){
            // Sector 7
                    L = -5;
                    R = 5;
                }

          if(-7*(Math.PI/8)<angle && angle< -5*(Math.PI/8)){
            // Sector 8
                    L = 0;
                    R = 5;
          }
          
          if(7*(Math.PI/8)<angle || angle< -7*(Math.PI/8)){
            // Sector 1
            L = 5;
            R = 5;
          }
          
          if(5*(Math.PI/8)<angle && angle< 7*(Math.PI/8)){
            // Sector 2
            L = 5;
            R = 0;
          }

          if(3*(Math.PI/8)<angle && angle< 5*(Math.PI/8)){
            // Sector 3
            L = 5;
            R = -5;
          }

          if(1*(Math.PI/8)<angle && angle< 3*(Math.PI/8)){
          // Sector 4
            L = 0;
            R = -5;
          }


                L = L * (multiplier / 5);
                R = R * (multiplier / 5);
                console.log(L, R);
                return (L * (multiplier / 5), R * (multiplier / 5));

       
        }
            
            function elementDragTouch(e) {
                // calculate the new cursor position:
               
                // calculate the cursor position:
                pos3 = Math.floor(e.touches[0].clientX);
                pos4 = Math.floor(e.touches[0].clientY);
                console.log(pos3, pos4);

                mag = Math.sqrt((pos3 - (50 + leftval)) ** 2 + (pos4 - (50 + topval)) ** 2) //determine distance from centre mouse is at
                //Note!!! 250,250 is centre of circle 

                var multiplier = 0;  //This determines the power to each motor, 5 is full power
                var angle = Math.atan2((pos3 - (50 + leftval)), (pos4 - (50 + topval))); //This is used to determine the motor's individual power for turning/direction

                // If mouse goes outside circle set maximum distance circle can move
                if (mag > 200) {
                    // set the joystick's new position (inside cirle but mouse outside circle):
                    // 200 is the radius of outer circle
                    elmnt.style.top = topval + (pos4 - (50 + topval)) * (200 / mag) + "px";
                    elmnt.style.left = leftval + (pos3 - (50 + leftval)) * (200 / mag) + "px";
                }

                else {
                    // set the joystick's new position:
                    elmnt.style.top = (pos4 - 50) + "px";
                    elmnt.style.left = (pos3 - 50) + "px"; //elmnt.offsetLeft - pos1
                }

                //Setting  multiplier by determining range in which magnitude is located
                if (0 < mag && mag < 50) {
                    multiplier = 0;
                }

                if (50 < mag && mag < 100) {
                    multiplier = 1;
                }

                if (100 < mag && mag < 150) {
                    multiplier = 3;
                }

                if (150 < mag) {
                    multiplier = 5;
                }

                if (-(Math.PI / 8) < angle && angle < (Math.PI / 8)) {
                    // Sector 5
                    L = -5;
                    R = -5;
                }

                if (-3 * (Math.PI / 8) < angle && angle < -(Math.PI / 8)) {
                    // Sector 6
                    L = 0;
                    R = -5;
                }

                if (-5 * (Math.PI / 8) < angle && angle < -3 * (Math.PI / 8)) {
                    // Sector 7
                    L = 5;
                    R = -5;
                }

                if (-7 * (Math.PI / 8) < angle && angle < -5 * (Math.PI / 8)) {
                    // Sector 8
                    L = 5;
                    R = 0;
                }

                if (7 * (Math.PI / 8) < angle || angle < -7 * (Math.PI / 8)) {
                    // Sector 1
                    L = 5;
                    R = 5;
                }

                if (5 * (Math.PI / 8) < angle && angle < 7 * (Math.PI / 8)) {
                    // Sector 2
                    L = 0;
                    R = 5
                }

                if (3 * (Math.PI / 8) < angle && angle < 5 * (Math.PI / 8)) {
                    // Sector 3
                    L = -5;
                    R = 5;
                }

                if (1 * (Math.PI / 8) < angle && angle < 3 * (Math.PI / 8)) {
                    // Sector 4
                    L = -5;
                    R = 0;
                }


                L = L * (multiplier / 5);
                R = R * (multiplier / 5);
                return (L, R);

                
            }

            function closeDragElement(e) {

                document.ontouchmove = null;
                document.ontouchend = null;

                document.onmouseup = null;
                document.onmousemove = null;

                elmnt.style.top =  topval +"px";
                elmnt.style.left = leftval + "px";
                
                SendUrl(0,0);
                                
                clearInterval(send);

                SendUrl(0,0);
          //elmt.style.top = 0+ "px";
          //elmt.style.left = 0 +"px";}
        
          /* stop moving when mouse button is released:*/
                //set motors to off:

            }

            console.log(pos3, pos4);
        }


    </script>


</html>)=====";

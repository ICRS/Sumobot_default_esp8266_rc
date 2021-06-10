const char MAIN_PAGE[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en" xmlns="http://www.w3.org/1999/xhtml">
  <head>
      <meta charset="utf-8" />
      <style>
          input {
              border: none;
              color: white;
              padding: 15px 32px;
              text-align: center;
              text-decoration: none;
              display: inline-block;
              font-size: 16px;
              margin: 4px 2px;
              cursor: pointer;
              background-color: #4CAF50;

              
          }

          .buttoncontainer {

              align-items: center;
              display: flex;
              justify-content: center;
          }

          
          /* Green */

          p {
              text-align: center;
          }

          h1 {
              text-align: center;
          }
      </style>

      <title>Main page</title>
      <script>
        function toPage(page) {
          if (page == "control_1") {
            //go to /control_1
            window.location.href = "/control_1"; //sliders
          } else if (page == "control_2") {
            //go to /control_2
            window.location.href = "/control_2"; //joystick
          } else if (page == "control_3") {
            //go to /control_3
            window.location.href = "/control_3";
          } else if (page == "control_custom") {
            //go to /control_custom
            window.location.href = "/control_custom";
          }
        }
      </script>
  </head>


  <body>
      <h1>Main page</h1>
      <p> You shall not pass </p>


    <div class="buttoncontainer">
      <p>
        <input type="submit" class="btn" value="Control 1" onclick="toPage('control_1')">
        <br><br>
        <input type="submit" class="btn" value="Control 2" onclick="toPage('control_2')">
        <br><br>
        <input type="submit" class="btn" value="Control 3" onclick="toPage('control_3')">

      </p>

    </div>
            
    <div class="buttoncontainer">
        <input type="submit" class="btn" value="Custom Control" onclick="toPage('control_custom')">
    </div>
  </body>
</html>
)=====";

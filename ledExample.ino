#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* SSID = "RC Car";  // SSID here
const char* PASSWORD = "12345678";  //Enter PASSWORD here

IPAddress staticIP(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

ESP8266WebServer server(80);

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<body>
  <h2>ESP Web Server</h2>
  <button onclick="switchOnOff()">ON/OFF</button>

<script>
function switchOnOff(){
  let xhr = new XMLHttpRequest();
  xhr.open("POST", "/switch");
  xhr.send();
}
</script>
</body>
</html>
)rawliteral";

void handle_OnConnect(){    /* setup on connect to 192.168.1.1 */
  server.send(200,"text/html", index_html);
}

bool on_off;

void handle_OnSwitch(){    /* setup on connect to 192.168.1.1 */
  on_off = !on_off;
  server.send(204,"text/html");
}

void handle_NotFound(){   /* if connect to not 192.168.1.1*/
  server.sendHeader("Location","/", true);
  server.send(302);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(D5, OUTPUT);
  on_off = true;
  digitalWrite(D5, on_off);
  WiFi.softAP(SSID, PASSWORD, 6, false, 1);
  WiFi.softAPConfig(staticIP, gateway, subnet);

  //sets up what server does at each url 
  server.on("/", handle_OnConnect);
  server.on("/switch", handle_OnSwitch);

  server.onNotFound(handle_NotFound);
  server.begin(); //start server
  
}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();  
  digitalWrite(D5, on_off);
}

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* SSID = "RC Car";  // SSID here
const char* PASSWORD = "12345678";  //Enter PASSWORD here

IPAddress staticIP(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

ESP8266WebServer server(80);

void handle_OnConnect(){    /* setup on connect to 192.168.1.1 */
  server.send(200,"text/html", "HELLO!");
}

void handle_NotFound(){   /* if connect to not 192.168.1.1*/
  server.sendHeader("Location","/", true);
  server.send(302);
}

void setup() {
  // put your setup code here, to run once:
  WiFi.softAP(SSID, PASSWORD, 6, false, 1);
  WiFi.softAPConfig(staticIP, gateway, subnet);

  //sets up what server does at each url 
  server.on("/", handle_OnConnect);

  server.onNotFound(handle_NotFound);
  server.begin(); //start server
  
}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();  
}

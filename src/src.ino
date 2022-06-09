/*
Here is the code that you need to upload to the Arduino
To use your device as the remote, connect to the SSID, type 192.168.1.1 - the gateway IP address and load the page
*/

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>

WebSocketsServer webSocket = WebSocketsServer(81);

//include webpages
#include "CONTROL.h"

/* Put your SSID & PASSWORD */
const char* SSID = "RC Car";  // SSID here
const char* PASSWORD = "12345678";  //Enter PASSWORD here

/* Put IP Address details */
IPAddress staticIP(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

ESP8266WebServer server(80);

//Left control pins 
const byte LEDLeft = D7;
const byte LEDLF = D6;    
const byte LEDLB = D5;

unsigned int LEDLeftint = 0; //LEFT value wheel control

bool LEDLFbit;  //sets direction motor spins variables (refer to L298m H bridge)

//Right control
const byte LEDRight = D1;
const byte LEDRF = D2;    
const byte LEDRB = D3;

unsigned int LEDRightint = 0;

bool LEDRFbit;

void handle_OnConnect();

void setup() {

  // Init Serial - Debug
  Serial.begin(115200);
  
  // code starts here
  //set pins to outputs
  //Left motor pins
  pinMode(LEDLeft, OUTPUT);
  pinMode(LEDLF, OUTPUT);
  pinMode(LEDLB, OUTPUT);
    
  //Right motor pins
  pinMode(LEDRight, OUTPUT);
  pinMode(LEDRF, OUTPUT);
  pinMode(LEDRB, OUTPUT);

  
  //set up wifi stuff
  WiFi.softAP(SSID, PASSWORD, 6, false, 1);
  WiFi.softAPConfig(staticIP, gateway, subnet);

  //sets up what server does at each url 
  server.on("/", handle_OnConnect);
    
  server.onNotFound(handle_NotFound);
  server.begin(); //start server
  // not required: Serial.println("HTTP server started");

  //websocket stuff
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);

}

void loop() {
  
  webSocket.loop();
  server.handleClient();  
    
  // setting LED left and right values
  digitalWrite(LEDLF,LEDLFbit);
  digitalWrite(LEDLB,!(LEDLFbit));
  
  digitalWrite(LEDRF,LEDRFbit);
  digitalWrite(LEDRB,!(LEDRFbit));

  // set PWM values
  analogWrite(LEDLeft, LEDLeftint);
  analogWrite(LEDRight, LEDRightint); 

  if(WiFi.softAPgetStationNum()==0){
    LEDLeftint = 0;
    LEDRightint = 0;
  } 
}

void handle_OnConnect(){    /* setup on connect to 192.168.1.1 */
  server.send(200,"text/html", CONTROL);
}

void handle_NotFound(){   /* if connect to not 192.168.1.1*/
  server.sendHeader("Location","/", true);
  server.send(302);
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length)
{
  switch(type) 
  {
      
    case WStype_DISCONNECTED:
      Serial.println("Client disconnnected !"+ num);
      break;
        
    case WStype_CONNECTED:
      {
        IPAddress ip = webSocket.remoteIP(num);
        Serial.println("Websocket client connnected !");        
        // send message to client
        webSocket.sendTXT(num, "Connected");                
      }
      break;
        
    case WStype_TEXT:
      String parse_payload;
      
      for(int i = 0; i < length;  i++){
        parse_payload.concat((char) payload[i]);
      }

      Serial.println(parse_payload);

      if(String(parse_payload[0]) == "l"){
        int x = parser_x(parse_payload);
        int y = parser_y(parse_payload);

        Serial.print(x); Serial.print(","); Serial.println(y);
        
        LEDLeftint = abs(x)*200;
        LEDRightint = abs(y)*200;

        Serial.println(LEDLeftint); Serial.println(LEDRightint);
        if(x <0){
          LEDLFbit = 0;
        }

        else{
          LEDLFbit = 1;
        }

        if(y<0){
          LEDRFbit = 0;
        }

        if(y>=0){
          LEDRFbit = 1;
        }
      }
  }
}

int parser_x(String data){
  data.remove(data.indexOf("r"));
  data.remove(data.indexOf("l"),1);
  return data.toInt();
}

int parser_y(String data){
  data.remove(0,data.indexOf("r")+1);
  data.remove(data.indexOf("r"),1);
  return data.toInt();
}

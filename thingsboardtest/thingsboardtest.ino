#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "SoftwareSerial.h"
#include <ThingsBoard.h>
#include <ArduinoJson.h>
#include "HX711.h"

#define DOUT  2
#define CLK  3

HX711 scale;

float calibration_factor = +163400; //Depending on the scale may need to adjust + or -, this gives us accurate result for our scale.

#define WIFI_AP "BrindLetting01"
#define WIFI_PASSWORD "Brind1234!"

#define TOKEN "SATgq882Pr0CB7OXvQTg"

char thingsboardServer[] = "demo.thingsboard.io";




WiFiClient wifiClient;
PubSubClient client(wifiClient);
int status = WL_IDLE_STATUS;
unsigned long lastSend;

void setup() {
  Serial.begin(115200);
  scale.begin(DOUT, CLK);
  //scale.set_scale();
  //scale.tare(); //Reset the scale to 0
  
  WiFi.begin(WIFI_AP, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("connected to");
  Serial.println(WIFI_AP);
  client.setServer( thingsboardServer, 1883 );

  

 
}

void loop() {
  if ( !client.connected() ) 
{
    reconnect();
    
}
//scale.set_scale(calibration_factor); //Adjust to this calibration factor

 
  sendWeightReadings();
    delay(5000);
}

void sendWeightReadings()
{
  String payload = "{";
  //if(scale.get_units() > -3 && scale.get_units() < 0){
   //payload += "\"weight\":";payload += 0;
  //}
  //else
  //{
    //payload += "\"weight\":";payload += scale.get_units() * 453.59237;
  //}
  payload += "}";
  // Prepare a JSON payload string
  
 //payload += "\"weight\":";payload += 60; payload += ",";
 payload += "\"weight\":";payload += 25;
   

  char attributes[1000];
  payload.toCharArray( attributes, 1000 );
  client.publish( "v1/devices/me/telemetry",attributes);
  Serial.println( attributes );
   
}
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    status = WiFi.status();
    if ( status != WL_CONNECTED) {
      WiFi.begin(WIFI_AP, WIFI_PASSWORD);
      while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
      }
      Serial.println("Connected to AP");
    }
    Serial.print("Connecting to ThingsBoard node ...");
    // Attempt to connect (clientId, username, password)
    if ( client.connect("Esp8266", TOKEN, NULL) ) {
      Serial.println( "[DONE]" );
    } else {
      Serial.print( "[FAILED] [ rc = " );
      Serial.println( " : retrying in 5 seconds]" );
      delay( 500 );
    }
  }
}

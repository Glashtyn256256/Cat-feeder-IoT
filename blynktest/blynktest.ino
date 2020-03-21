#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include "HX711.h"
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include <StreamUtils.h>

SoftwareSerial s(D6,D5);


char auth[] = "KI5X0r2UxFp3zDvToscJpNlj8f1PiE2K"; //Enter the Auth codethat is given to you by blynk

char ssid[] = "BrindLetting01";  //Enter your WIFI Name
char pass[] = "Brind1234!";  //Enter your WIFI Password



float calibration_factor = +163400;
int totalWeight;
SimpleTimer timer;

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void sendWeightReadings()
{
    Blynk.virtualWrite(V7,totalWeight);  //add the value set in the app
}

BLYNK_WRITE(V6) //Read from the value set in the blynk app from v6 pin
{
//  test = param.asInt();
}

void setup()
{
   
   s.begin(115200);
   Serial.begin(115200); // See the connection status in Serial Monitor
 //  pinMode(D7, INPUT);

  //  pinMode(D8, OUTPUT);
   while (!Serial) continue;
 // Blynk.begin(auth, ssid, pass);
 
  //Gets called every second
 // timer.setInterval(1000L, sendWeightReadings);
}


void loop()
{
//int data;
delay(1000);
if(s.available()>0){
 StaticJsonDocument<1000> jsonDoc;
 //s.println(s);
 //ReadLoggingStream loggingStream(s, Serial);
 DeserializationError err = deserializeJson(jsonDoc, s);

 //JsonObject root = jsonDoc.as<JsonObject>();
 // auto error = deserializeJson(jsonDoc, s);
//  Serial.println(object["weight"]);
 //const char* ttotalWeight = jsonDoc["weight"];
 // Serial.println(ttotalWeight);
if (err) {
    Serial.print(F("deserializeJson() failed with code "));
    Serial.println(err.c_str());
    return;
}

totalWeight = jsonDoc["weight"];
Serial.println(totalWeight);
}
}

//StaticJsonBuffer<1000> jsonBuffer;
//  JsonObject& root = jsonBuffer.parseObject(s);
//  //root.printTo(Serial);
//  if (root == JsonObject::invalid())
//  {
//    Serial.println("fail");
//    return;
//  }
//  Serial.println("JSON received and parsed");
//  root.prettyPrintTo(Serial);
//  Serial.print("Data 1 ");
//  Serial.println("");
//  int data1=root["data1"];
//  Serial.print(data1);
//  Serial.print("   Data 2 ");
//  int data2=root["data2"];
//  Serial.print(data2);
//  Serial.println("");
//  Serial.println("---------------------xxxxx--------------------");
 

//  Blynk.run(); // Initiates Blynk
//  timer.run(); // Initiates SimpleTimer
  

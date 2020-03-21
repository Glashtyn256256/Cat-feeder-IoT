#include "HX711.h"
#include <SoftwareSerial.h>
#include <ArduinoJson.h>

SoftwareSerial s(5,6); //rx, tx

#define DOUT  3
#define CLK  2

HX711 scale;

float calibration_factor = +163000; //Depending on the scale may need to adjust + or -, 163400 gives us accurate result for our scale.
//The surface you have the wieght on will effect the weight. Make sure it's on a solid surface for best readsings.

float totalWeight;
const int capacity = JSON_OBJECT_SIZE(1);

void setup() {
//  Serial.begin(9600);
  s.begin(115200);
  Serial.begin(115200);
  scale.begin(DOUT, CLK);
  scale.set_scale();
  scale.tare(); //Reset the scale to 0

//This can be used to remove the need to tare the scale. Useful in permanent scale projects.
  long zero_factor = scale.read_average(); //Get a baseline reading
   scale.set_scale(calibration_factor); //Use the calibiration factor that you
   
}
//6 has different naming conventions
StaticJsonDocument<1000> jsonDoc;
//JsonObject object = jsonDoc.to<JsonObject>();
void loop() {

  //JsonObject root = jsonDoc.as<JsonObject>();
 // Serial.print("Reading: ");
  if(scale.get_units() > -3 && scale.get_units() < 0){
    //Serial.print(0);
    totalWeight = 0;
  }
  else
  {
    totalWeight = scale.get_units() * 453.59237;
    //Serial.print(totalWeight, 0); //Units are in lbs changing to grams
  }
//  Serial.println(" grams");
  jsonDoc["weight"].set(totalWeight);
 // jsonDoc["raw"] = serialized("[1]");
 // int test = (int) totalWeight;
  //delay(1000);
  //jsonDoc["weight"] = "help";
 //StaticJsonBuffer<1000> jsonBuffer;
 //JsonObject& root = jsonBuffer.createObject();
 // root["data1"] = 100;
  //root["data2"] = 200;
  // root.printTo(Serial);
//  if(s.available()>0)
 // {
     //test = s.read();
   // Serial.print("hello");
   // s.write(test);
    //s.println("test is availiable");
    
    serializeJson(jsonDoc, s);
    delay(1000);
   // root.printTo(Serial);
   
  // root.printTo(Serial);
    //root.printTo(s);
 // }
}

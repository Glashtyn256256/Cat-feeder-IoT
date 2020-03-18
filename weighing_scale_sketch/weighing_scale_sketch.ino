#include "HX711.h"

#define DOUT  3
#define CLK  2

HX711 scale;

float calibration_factor = +163400; //Depending on the scale may need to adjust + or -, 163400 gives us accurate result for our scale.

void setup() {
  Serial.begin(9600);
  scale.begin(DOUT, CLK);
  scale.set_scale();
  scale.tare(); //Reset the scale to 0

//This can be used to remove the need to tare the scale. Useful in permanent scale projects.
  long zero_factor = scale.read_average(); //Get a baseline reading
   scale.set_scale(calibration_factor); //Use the calibiration factor that you
}

void loop() {

  Serial.print("Reading: ");
  if(scale.get_units() > -3 && scale.get_units() < 0){
    Serial.print(0);
  }
  else
  {
    Serial.print(scale.get_units() * 453.59237, 0); //Units are in lbs changing to grams
  }
  Serial.print(" grams"); 
}

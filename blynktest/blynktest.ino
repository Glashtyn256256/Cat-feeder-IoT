#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include "HX711.h"
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>



char auth[] = "KI5X0r2UxFp3zDvToscJpNlj8f1PiE2K"; //Enter the Auth codethat is given to you by blynk

char ssid[] = "BrindLetting01";  //Enter your WIFI Name
char pass[] = "";  //Enter your WIFI Password

#define DOUT  3
#define CLK  2

HX711 scale;

float calibration_factor = +163400;
int test;
SimpleTimer timer;

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void sendWeightReadings()
{
    Blynk.virtualWrite(V7,test);  //add the value set in the app
}

BLYNK_WRITE(V6) //Read from the value set in the blynk app from v6 pin
{
  test = param.asInt();
}

void setup()
{
  Serial.begin(115200); // See the connection status in Serial Monitor
  Blynk.begin(auth, ssid, pass);



  //Gets called every second
  timer.setInterval(1000L, sendWeightReadings);
}

void loop()
{
  Blynk.run(); // Initiates Blynk
  timer.run(); // Initiates SimpleTimer
}

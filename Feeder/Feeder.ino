
#include <Servo.h>

Servo myservo;  // create servo object to control a servo

int pos = 0;    // variable to store the servo position

void setup() {
  Serial.begin(9600);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
    // Initially the servo must be stopped 
   // myservo.write(40);
    myservo.write(180);
    //180 closed
    //40 open
    //
}

void loop() {
  if (Serial.available() > 0) {
    char cmd = (char) Serial.read();
    if (cmd == '1') {
      for (pos = 180; pos >= 30; pos -= 1) { // goes from 180 degrees to 0 degrees
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
       // delay(5);                       // waits 15ms for the servo to reach the position#
        Serial.println(pos);
      }
      delay(250);   
        for (pos = 30; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
          // in steps of 1 degree
          myservo.write(pos);              // tell servo to go to position in variable 'pos'
         // delay(5);
          Serial.println(pos);
        }
      }
    }
  }

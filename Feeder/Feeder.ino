#include <Servo.h>

//180 closed position 
//40 open position
 
Servo myservo;  // create servo object to control a servo
int pos = 0;    // variable to store the servo position
int openPos = 20;
int closedPos = 180;

void setup() {
  Serial.begin(9600);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo.write(closedPos); // Initially the servo must be moved to closed position
}

void loop() {
  if (Serial.available() > 0) {     
    char cmd = (char) Serial.read();
    if (cmd == '1') {
      for (pos = closedPos; pos >= openPos; pos -= 1) { // goes from closed position (180 degrees )to open poisition (20 degrees)
        myservo.write(pos);              // tell servo to go to position in variable 'pos'                 
        Serial.println(pos);
      }
      delay(250);   
        for (pos = openPos; pos <= closedPos; pos += 1) { // goes from open position (20 degrees) to closed position (180 degrees)
          // in steps of 1 degree
          myservo.write(pos);              // tell servo to go to position in variable 'pos'
          Serial.println(pos);
        }
      }
    }
  }

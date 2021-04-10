// Include the Servo library 
#include <Servo.h> 


// Declare the pins
#define SERVO_PIN 9
#define PIN 3
#define LIMIT_SWITCH 4

// Define variables
int pinValue;
int swiValue;
int previous1 = 0;
int previous2 = 0;

// Create a servo object 
Servo Servo1; 


void setup() { 
   // We need to attach the servo to the used pin number 
   Servo1.attach(SERVO_PIN); 
   pinMode(PIN, INPUT);
   pinMode(LIMIT_SWITCH, INPUT_PULLUP);
}

void loop() {
  pinValue = digitalRead(PIN);
  if (pinValue == HIGH){
    for (int i=0; i<=180; i+=15){
      swiValue = digitalRead(LIMIT_SWITCH);
      if (swiValue == 0 && previous1 == 0){
        Servo1.write(i);
        }else if (swiValue == 1 && previous1 == 0){
          break;
        }
        previous1 == swiValue;
      }
  }else if (pinValue == LOW){
      for (int i=180; i>=0; i-=15){
        swiValue = digitalRead(LIMIT_SWITCH);
        if (swiValue == 0 && previous2 == 0){
          Servo1.write(i);
        }else if (swiValue == 1 && previous2 == 0){
          break;
        }
        previous2 == swiValue;
      }
   }
}

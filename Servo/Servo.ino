// Include the Servo library 
#include <Servo.h> 


// Declare the pins
#define SERVO_PIN 9
#define PIN 3
#define LIMIT_SWITCH1 4
#define LIMIT_SWITCH2 5

// Define variables
int pinValue;
int swiValue1;
int swiValue2;
int previous1 = 0;
int previous2 = 0;

// Create a servo object 
Servo Servo1; 


void setup() { 
   // We need to attach the servo to the used pin number 
   Servo1.attach(SERVO_PIN); 
   pinMode(PIN, INPUT);
   pinMode(LIMIT_SWITCH1, INPUT);
   pinMode(LIMIT_SWITCH2, INPUT);
}

void loop() {
  pinValue = digitalRead(PIN);
  if (pinValue == HIGH){
    for (int i=0; i<=180; i+=15){
      swiValue1 = digitalRead(LIMIT_SWITCH1);
      if (swiValue1 == 0 && previous1 == 0){
        Servo1.write(i);
        }else if (swiValue1 == 1 && previous1 == 0){
          break;
        }
        previous1 == swiValue1;
      }
  }else if (pinValue == LOW){
      for (int i=180; i>=0; i-=15){
        swiValue2 = digitalRead(LIMIT_SWITCH2);
        if (swiValue2 == 0 && previous2 == 0){
          Servo1.write(i);
        }else if (swiValue2 == 1 && previous2 == 0){
          break;
        }
        previous2 == swiValue2;
      }
   }
}

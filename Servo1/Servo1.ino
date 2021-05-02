#include <Servo.h> 

Servo servo1;

const int flexpin = A0; 

int flexposition;    // Input value from the analog pin.
int servoposition;   // Output value to the servo.

void setup() 
{ 
  // Use the serial monitor window to help debug our sketch:

  Serial.begin(9600);

  // Enable control of a servo on pin 9:

  servo1.attach(9);
} 


void loop() 
{ 
  // Read the position of the flex sensor (0 to 1023):

  flexposition = analogRead(flexpin);

  // Because the voltage divider circuit only returns a portion
  // of the 0-1023 range of analogRead(), we'll map() that range
  // to the servo's range of 0 to 180 degrees. The flex sensors
  // we use are usually in the 600-900 range:

  servoposition = map(flexposition, 950, 1023, 0, 180);
  servoposition = constrain(servoposition, 0, 180);

  // Now we'll command the servo to move to that position:

  servo1.write(servoposition);

  // Because every flex sensor has a slightly different resistance,
  // the 600-900 range may not exactly cover the flex sensor's
  // output. To help tune our program, we'll use the serial port to
  // print out our values to the serial monitor window:

  Serial.print("sensor: ");
  Serial.print(flexposition);
  Serial.print("  servo: ");
  Serial.println(servoposition);

  delay(500);  // wait 20ms between servo updates
} 

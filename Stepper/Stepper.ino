#include <Stepper.h>
#define  STEPS  600    // steps per revolution (limited to 315°)
#define  COIL1  8
#define  COIL2  9
#define  COIL3  10
#define  COIL4  11

#define PotIn  0

// create an instance of the stepper class:
Stepper stepper(STEPS, COIL1, COIL2, COIL3, COIL4);

void setup() {
  stepper.setSpeed(60);    // set the motor speed to 30 RPM (360 PPS aprox.).
  stepper.step(600);       //Reset Position(630 steps counter-clockwise).
  Serial.begin(9600);    //for debuging.
}
int pos = 0;               //Position in steps(0-600)= (0°-315°)

void loop() {
  int val = analogRead(PotIn);   //get the potentiometer value (range 0-1023)
  val = map(val, 0, 1023, 0, 600); // map pot range in the stepper range.

  if (abs(val - pos) > 2) {      //if diference is greater than 2 steps.
    if ((val - pos) > 0) {
      stepper.step(-1);      // move one step to the left.
      pos++;
    }
    //  delay(25);
    if ((val - pos) < 0) {
      stepper.step(1);       // move one step to the right.
      pos--;
    }
    //   delay(25);
  }
  Serial.println(pos);      //for debuging...
  //  Serial.println(val);
  //  delay(100);
}

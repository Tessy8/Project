#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();   // Initiates library.

#define SERVOMIN  100  // Minimum pulse length count out of 4096.
#define SERVOMAX  2200 // Maximum pulse length count out of 4096.
#define FREQUENCY 60

// Potentiometer pins
#define POTPIN1 A0
#define POTPIN2 A1
#define POTPIN3 A2
#define POTPIN4 A3
#define POTPIN5 A4
#define POTPIN6 A5

// Servo pins
#define servo1 3
#define servo2 4
#define servo3 5
#define servo4 6
#define servo5 7
#define servo6 8


void setup() {
  // Set potentiometers as input
  pinMode(POTPIN1, INPUT);
  pinMode(POTPIN2, INPUT);
  pinMode(POTPIN3, INPUT);
  pinMode(POTPIN4, INPUT);
  pinMode(POTPIN5, INPUT);
  pinMode(POTPIN6, INPUT);
  
  pwm.begin();         // Sends PWM signals.
  pwm.setPWMFreq(FREQUENCY);  // Makes servos run at 60 Hz rate.
  delay(20);
}


void moveServo(int potIn, int servoOut)
{
  int pulse_wide, pulse_width, potVal;
  
  // Read values from potentiometer
  potVal = analogRead(potIn);
  
  // Convert to pulse width
  pulse_wide = map(potVal, 0, 1023, SERVOMIN, SERVOMAX);
  pulse_width = int(float(pulse_wide) / 1000000 * FREQUENCY * 4096);
  
  //Control Motor
  pwm.setPWM(servoOut, 0, pulse_width);
 
}
 
void loop() {
 
  //Control First Servo
  moveServo(POTPIN1, servo1);

  //Control Second Servo
  moveServo(POTPIN2, servo2);

  //Control Third Servo
  moveServo(POTPIN3, servo3);

  //Control Fourth Servo
  moveServo(POTPIN4, servo4);

  //Control Fifth Servo
  moveServo(POTPIN5, servo5);

  //Control Sixth Servo
  moveServo(POTPIN6, servo6);
  
}

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
int angle = 80;
bool once = true;
int servoDelay = 100;
bool once2 = true;

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);
Adafruit_PWMServoDriver pwm2 = Adafruit_PWMServoDriver(0x41);

#define MIN_PULSE_WIDTH 650
#define MAX_PULSE_WIDTH 2350
#define DEFAULT_PULSE_WIDTH 1500
#define FREQUENCY 50
int close = 40;
int open = 120;
int neutral = 80;
uint8_t servonum = 0;

int button_read[] = {};
int led[] = {0, 0, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52};
int counter[] = { 0, 0, 0, 0, 0, 0,  0 , 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

bool done = true;
bool done2 = true;

void setup() {
  Serial.begin(9600);
  Serial.println("24 channel Servo code!");
  pwm.begin();
  pwm.setPWMFreq(FREQUENCY);
  pwm2.begin();
  pwm2.setPWMFreq(FREQUENCY);
  for (int i = 2; i < 27; i++) {
    pinMode(i, INPUT_PULLUP);
  }
  for (int i = 27; i < 53; i++) {
    pinMode(i, OUTPUT);
  }
}
int pulseWidth(int angle) {
  int pulse_wide, analog_value;
  pulse_wide = map(angle, 0, 180, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  analog_value = int(float(pulse_wide) / 1000000 * FREQUENCY * 4096);
  Serial.println(analog_value);
  return analog_value;
}

void loop() {
  for (int i = 2; i < 27; i++) {
    button_read[i] = digitalRead(i);
  }

  for (int i = 2; i < 27; i++) {
    if ( button_read[i] == LOW && i < 15) {
      counter[i] = counter[i] + 1;
      delay(50);
      Serial.println(i);
      Serial.println(counter[i]);
      if (counter[i] == 1) {
        digitalWrite(led[i], HIGH);
        //b_do(i, close);
      } else if (counter[i] == 2) {
        digitalWrite(led[i], LOW);
        // b_do(i, open);
        counter[i] = 0;
      }
    } else if ( button_read[i] == LOW && i > 14) {
      counter[i] = counter[i] + 1;
      delay(50);
      Serial.println(i);
      Serial.println(counter[i]);
      if (counter[i] == 1) {
        digitalWrite(led[i], HIGH);
        //b_do2(i, close);
      } else if (counter[i] == 2) {
        digitalWrite(led[i], LOW);
        // b_do2(i, open);
        counter[i] = 0;
      }
    }
    // Serial.println("done");
  }
}
void b_do(int num, int pos) {
  num = num - 2;
  pwm.wakeup();
  pwm.setPWM(num, 0, pulseWidth(pos));
  delay(servoDelay);
  pwm.sleep();
}
void b_do2(int num, int pos) {
  num = num - 2;
  pwm2.wakeup();
  pwm2.setPWM(num, 0, pulseWidth(pos));
  delay(servoDelay);
  pwm2.sleep();
}

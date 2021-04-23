// Connect the SCL and SDA pins of the DS3231 RTC Module to the SCL(A5) and SDA(A4) pins of Arduino
// Connect the VCC of DS3231 RTC Module to 5V of Arduino and the GND of DS3231 RTC Module to GND of Arduino
// Connect the Red LED to pin 3 of Arduino, Green LED to pin 4 of Arduino and Yellow LED to pin 5 of Arduino

// Include Wire and RTClib library. Download from Tools>Manage Libraries
#include "RTClib.h"
#include <Wire.h>


RTC_DS3231 rtc;   // Initialize DS3231

// define the pins of the LEDs
#define RED 3
#define GREEN 4
#define YELLOW 5


void setup () {
  // Ensure that the RTC module is connected
  Wire.begin();
  rtc.begin();

  // Set the LEDs as output
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(YELLOW, OUTPUT);

  // Set default states of the LEDs to low
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(YELLOW, LOW);
}

void loop () {
  DateTime now = rtc.now();     // gets the current date and time

  //hh - the hour with a leading zero (00 to 23)
  //mm - the minute with a leading zero (00 to 59)
  //ss - the whole second with a leading zero where applicable (00 to 59)

  // Check if the time is 06:30 and turns on yellow LED
  if ((now.hour() == 06) && (now.minute() == 30)){
    digitalWrite(YELLOW, HIGH);
    digitalWrite(RED, LOW);
  }

  // Check if the time is 07:00 and turns on green LED
  if ((now.hour() == 07) && (now.minute() == 00)){
    digitalWrite(GREEN, HIGH);
    digitalWrite(YELLOW, LOW);
  }

  // Check if the time is 19:00 and turns on red LED
  if ((now.hour() == 19) && (now.minute() == 00)){
    digitalWrite(RED, HIGH);
    digitalWrite(GREEN, LOW);
  }
  
}

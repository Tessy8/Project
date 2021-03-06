// Code to select between two modes at the click of a button

#include <Wire.h>
#include <RTClib.h>
#include <DHT.h>

#define BUTTON 3        // Button Pin
#define DHTPIN 2        // DHT Pin
#define DHTTYPE DHT11   // DHT Type

// Variables for button switching
int btnValue;
int previous = 0;
int value = 0;

// Variable holding time
String str_time;
String str_temp;

// Variables holding time positions
int index_1;
int index_2;
int index_3;
int index_4;

// Variables holding temperature positions
int index_5;
int index_6;


// defining RTC and DHT parameter
RTC_DS3231 rtc;
DHT dht(DHTPIN, DHTTYPE);

// DateTime now;

void setup() {
  pinMode(BUTTON, INPUT);

  // Initialize RTC and DHT object
  rtc.begin();
  dht.begin();
}

// Temperature loop
void temp(){
  // Checks for first number in temperature
  index_5 = str_temp[0];
  switch(index_5){
    case 0:
      break;
    case 1:
      break;
    default:
      break;
  }
  
  // Checks for second number in temperature
  index_6 = str_temp[1];
  switch(index_6){
    case 0:
      break;
    case 1:
      break;
    case 2:
      break;
    case 3:
      break;
    case 4:
      break;
    case 5:
      break;
    case 6:
      break;
    case 7:
      break;
    case 8:
      break;
    case 9:
      break;
    default:
      break;
  }
}

// Time loop
void time_(){
  // Checks for first number in the time
  index_1 = str_time[0];
  switch(index_1){
    case 0:
      break;
    case 1:
      break;
    case 2:
      break;
    default:
      break;
  }

  // Checks for second number in the time
  index_2 = str_time[1];
  switch(index_2){
    case 0:
      break;
    case 1:
      break;
    case 2:
      break;
    case 3:
      break;
    case 4:
      break;
    case 5:
      break;
    case 6:
      break;
    case 7:
      break;
    case 8:
      break;
    case 9:
      break;
    default:
      break;
  }

  // Checks for third number in the time
  index_3 = str_time[2];
  switch(index_3){
    case 0:
      break;
    case 1:
      break;
    case 2:
      break;
    case 3:
      break;
    case 4:
      break;
    case 5:
      break;
    default:
      break;
  }

  // Checks for fourth number in the time
  index_4 = str_time[3];
  switch(index_4){
    case 0:
      break;
    case 1:
      break;
    case 2:
      break;
    case 3:
      break;
    case 4:
      break;
    case 5:
      break;
    case 6:
      break;
    case 7:
      break;
    case 8:
      break;
    case 9:
      break;
    default:
      break;
  }
  
}

void loop() {
  // read input from button
  btnValue = digitalRead(BUTTON);
  if (btnValue == 0 && previous == 0){
    if (value == 1){
      value = 0;
    }else{
      value = 1;
    }
  }
  
  switch (value) {
    case 0:
      temp();
      break;
    case 1:
      time_();
      break;
}
  previous == btnValue;
    
}

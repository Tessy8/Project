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
String str;
int index_1;
int index_2;
int index_3;
int index_4;

// Vriable holding time
String str;

// Variables holding time positions
int index_1;
int index_2;
int index_3;
int index_4;

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
  
}

// Time loop
void time_(){
  // Checks for first number in the time
  index_1 = str[0];
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
  index_2 = str[1];
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
  index_3 = str[2];
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
  index_4 = str[3];
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

// Index loop
void index(String str){
  index_1 = str.indexOf(1);
  switch (index_1){
    case 0:
      break;
    case 1:
      break;
    case 2:
      break;
    case 3:
      break;
  }

  index_2 = str.indexOf(2);
  switch (index_2){
    case 0:
      break;
    case 1:
      break;
    case 2:
      break;
    case 3:
      break;
  }

  index_3 = str.indexOf(3);
  switch (index_3){
    case 0:
      break;
    case 1:
      break;
    case 2:
      break;
    case 3:
      break;
  }

  index_4 = str.indexOf(4);
  switch (index_4){
    case 0:
      break;
    case 1:
      break;
    case 2:
      break;
    case 3:
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


  // ______________________
    
}

// Include Libraries
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <Servo.h> 


// Define Pin Numbers
#define SERVOPIN1 10
#define SERVOPIN2 11
#define SERVOPIN3 12


// Initialize Keypad
const byte ROWS = 4; 
const byte COLS = 4; 

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6}; 
byte colPins[COLS] = {5, 4, 3, 2}; 


// Create objects
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
LiquidCrystal_I2C lcd(0x21, 16, 2);
Servo Servo1;
Servo Servo2;
Servo Servo3;


// Define Variables
int candyType;
int amt = 0;



void setup() {
  lcd.backlight();
  lcd.init();
  Servo1.attach(SERVOPIN1); 
  Servo2.attach(SERVOPIN2); 
  Servo3.attach(SERVOPIN3); 
  
}

void loop() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("What candy will you like?");
  candyType = customKeypad.getKey();  
  if (candyType == 1){
   candyAmt(candyType); 
  }else if (candyType == 2){
    candyAmt(candyType);
  }else if (candyType == 3){
    candyAmt(candyType);
  }else{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Wrong Selection");
    delay(1000);
  }
}

// Function to dispense candy balls
void candyAmt(int NO){
  lcd.clear();
  lcd.print("How many candy will you like?");
  amt = customKeypad.getKey();
  switch (NO) {
    case 1:
      for (int i=0; i<amt; i++){
        Servo1.write(90);
        delay(1000);
        Servo1.write(0);
      }
      break;
    case 2:
      for (int i=0; i<amt; i++){
        Servo2.write(90);
        delay(1000);
        Servo2.write(0);
      }
      break;
    case 3:
      for (int i=0; i<amt; i++){
        Servo3.write(90);
        delay(1000);
        Servo3.write(0);
      }
      break;
    default:
      Servo1.write(0);
      Servo2.write(0);
      Servo3.write(0);
      break;
  }  
}

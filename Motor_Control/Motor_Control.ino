// Code to rotate motor from 0 to 100% in 30 seconds in both directions

#include <Keypad.h>

#define FORWARDPIN 11
#define REVERSEPIN 10

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

Keypad customKeypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

String num;                               // contains the input from keypad as a string
float number;                             // contains the input from keypad as an float
float motorIncrement;           

void setup() {
  // Set pins as output
  pinMode(FORWARDPIN, OUTPUT);
  pinMode(REVERSEPIN, OUTPUT);

  // Turn off motor - Initial State
  digitalWrite(FORWARDPIN, LOW);
  digitalWrite(REVERSEPIN, LOW);

  // Set maximum number of digit to be entered through keypad
  num.reserve(10);
}

void loop() {
  // Read input from keypad
  char key = customKeypad.getKey();
  if (key){
    if (key >= '0' && key <= '9'){
      num += key;                        // Add new character to string num
    }else if (key == '#'){
      if (num.length() > 0){
        number = num.toInt();            // Convert string to integer
        num = "";                        // Clear the input when # is pressed
        motorIncrement = 255/number;     // value for incrementing motor rotation
      }
    }else if (key == '*'){
      num = "";                       // Clear the input if a mistake is made when typing
    }
  }
  
  // Forward
  for (float motorValue = 0; motorValue <= 255; motorValue += motorIncrement){
    digitalWrite(REVERSEPIN, LOW);
    analogWrite(FORWARDPIN, motorValue);
    delay(1000);
  }
  // Reverse
  for (float motorValue = 0; motorValue <= 255; motorValue += motorIncrement){
    digitalWrite(FORWARDPIN, LOW);
    analogWrite(REVERSEPIN, motorValue);
    delay(1000);
  }
}

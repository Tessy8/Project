#include <LiquidCrystal.h>
#include <Keypad.h>

#define IR_PIN_SHORT A0
#define IR_PIN_LONG A1
#define CW_RELAY 6
#define ACW_RELAY 7

const byte ROWS = 4; 
const byte COLS = 4; 

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};


int counter_left = 1;    // Counter
int counter_right = 1;    // Counter
int longPoint; // Longer IR Sensor
int shortPoint; // Shorter IR Sensor
char customKey;     // number entered from Keypad
String num;         // number input from keypad
int number;         // stores num

byte rowPins[ROWS] = {9, 8, 7, 6}; 
byte colPins[COLS] = {5, 4, 3, 2}; 

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 


void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.setCursor(0,0);
  lcd.print("Welcome");

  pinMode(IR_PIN_SHORT, INPUT);
  pinMode(IR_PIN_LONG, INPUT);
  pinMode(CW_RELAY, OUTPUT);
  pinMode(ACW_RELAY, OUTPUT);
    
}

void loop() {
 
  char customKey = customKeypad.getKey();
  if (customKey){
    lcd.clear();
    if (customKey == '*'){                // Clear Screen
      num = "";
      lcd.clear();
    }else if (customKey == '#'){          // Enter
      number = num.toInt();
      num = "";
      lcd.clear(); 
      if (number > 45){
        digitalWrite(ACW_RELAY, HIGH);
        shortPoint = analogRead(IR_PIN_SHORT);
        while (shortPoint > 100){
          lcd.print(91 - counter_left);
          if (counter_left == number){
            digitalWrite(ACW_RELAY, LOW);
            delay(5000);
            lcd.clear();
            digitalWrite(CW_RELAY, HIGH);
            counter_left = 1;
            break;
          }
          counter_left++;
        }
      }else if (number < 45){
        digitalWrite(CW_RELAY, HIGH);
        shortPoint = analogRead(IR_PIN_SHORT);
        while(shortPoint > 100){
          lcd.print(counter_right);
          if (counter_right == number){
            digitalWrite(CW_RELAY, LOW);
            delay(5000);
            lcd.clear();
            digitalWrite(ACW_RELAY, HIGH);
            counter_right = 1;
            break;
          }
          counter_right++;
        }
      }
      longPoint = analogRead(IR_PIN_LONG);
        if (longPoint > 100){
          digitalWrite(ACW_RELAY, LOW);
          digitalWrite(CW_RELAY, LOW);
        }
    }else if (customKey == 'A'){
      lcd.clear();
    }else if (customKey == 'B'){
      lcd.clear();
    }else if (customKey == 'C'){
      lcd.clear();
    }else if (customKey == 'D'){
      lcd.clear();
    }else{
      lcd.print(customKey);
      num += customKey;
    }
  }

      
}

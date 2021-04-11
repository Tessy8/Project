int latchPin = 4; // pins connected to shift registors
int clockPin = 5;
int dataPin = 3;
int pins [9] = {2, 6, 7, 8, 9, 10, 11, 12, 13}; // common cathode pins
byte one[9] = { B001100, // Letters are defined
                B0100,// you can create your own
                B0100,
                B0100,
                B000100,
                B00100,
                B00100,
                B00100,
                B001110
            };

byte two[9] = { B111110, 
                B0001,
                B0001,
                B0001,
                B011110,
                B10000,
                B10000,
                B10000,
                B111111
            };

byte three[9] = { B011110, 
                  B0001,
                  B0001,
                  B0001,
                  B011110,
                  B00001,
                  B00001,
                  B00001,
                  B011110
            };

byte four[9] = {  B100010, 
                  B1010,
                  B1010,
                  B1010,
                  B111111,
                  B00010,
                  B00010,
                  B00010,
                  B000010
            };

byte five[9] = {  B111111, 
                  B1000,
                  B1000,
                  B1000,
                  B011110,
                  B00001,
                  B00001,
                  B00001,
                  B011110
            };

byte six[9] = {   B011111, 
                  B1000,
                  B1000,
                  B1000,
                  B111110,
                  B10001,
                  B10001,
                  B10001,
                  B011110
            };

byte seven[9] = { B111111, 
                  B0001,
                  B0001,
                  B0010,
                  B000100,
                  B01000,
                  B01000,
                  B01000,
                  B010000
            };

byte eight[9] = { B011110, 
                  B1001,
                  B1001,
                  B1001,
                  B011110,
                  B10001,
                  B10001,
                  B10001,
                  B011110
            };

byte nine[9] = {  B011110, 
                  B1001,
                  B1001,
                  B1001,
                  B011111,
                  B00001,
                  B00001,
                  B00001,
                  B111110
            };

byte zero[9] = {  B011110, 
                  B1001,
                  B1001,
                  B1001,
                  B100001,
                  B10001,
                  B10001,
                  B10001,
                  B011110
            };

byte o[9] = {     B011000, 
                  B1100,
                  B1100,
                  B1100,
                  B011000,
                  B00000,
                  B00000,
                  B00000,
                  B000000
            };

byte c[9] = {     B000000, 
                  B0000,
                  B0000,
                  B0000,
                  B011100,
                  B10000,
                  B10000,
                  B10000,
                  B011100
            };


void setup() {
  Serial.begin(9600); // Serial begin
  pinMode(latchPin, OUTPUT); // Pin configuration
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  for (int i = 0; i < 9; i++) { // for loop is used to configure common cathodes
    pinMode(pins[i], OUTPUT);
    digitalWrite(pins[i], HIGH);
  }

}

void loop() {
  display_char(one);
  delay(1000);
  display_char(two);
  delay(1000);
  display_char(three);
  delay(1000);
  display_char(four);
  delay(1000);
  display_char(five);
  delay(1000);
  display_char(six);
  delay(1000);
  display_char(seven);
  delay(1000);
  display_char(eight);
  delay(1000);
  display_char(nine);
  delay(1000);
  display_char(zero);
  delay(1000);
  display_char(o);
  delay(1000);
  display_char(c);
  delay(1000);
  


}
void display_char(byte ch[9]) { // Method do the multiplexing
  for (int j = 0; j < 9; j++) {
    digitalWrite(latchPin, LOW);
    digitalWrite(pins[j], LOW);

    shiftOut(dataPin, clockPin, LSBFIRST, ch[j]);
    digitalWrite(latchPin, HIGH);
    //delay(1);
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, B000000); // to get rid of flicker when
    digitalWrite(latchPin, HIGH);
    digitalWrite(pins[j], HIGH);

  }


}

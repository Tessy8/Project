#define FAN_PIN 8   // select the input pin for the relay connected to the fan
#define BUTTON_PIN 5  // select the input pin for the button


void setup() {
  pinMode(FAN_PIN, OUTPUT);   // declare the Relay pin as an OUTPUT
  pinMode(BUTTON_PIN, INPUT);   // declare the Button pin as an OUTPUT
}


void loop() {
  if (digitalRead(BUTTON_PIN) == HIGH) {  // read the button pin
    digitalWrite(FAN_PIN, HIGH);        // if high, turn relay on
  }
  else {
    digitalWrite(FAN_PIN, LOW);         // else, turn relay off
  }
}

#define BUTTON_PIN 2
#define FAN_PIN 7
#define LED_PIN 9

int val1;
int val2;
int buttonState;
int Mode = 0;
void setup() {
  pinMode(BUTTON_PIN, INPUT);
  pinMode(FAN_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  buttonState = digitalRead(BUTTON_PIN);
}
void loop() {
  val1 = digitalRead(BUTTON_PIN);
  delay(10);
  val2 = digitalRead(BUTTON_PIN);
  if (val1 == val2) {
    if (val1 != buttonState) {
      if (val1 == LOW) {
        if (Mode == 0) {
          Mode = 1;
        } else {
          if (Mode == 1) {
            Mode = 2;
          } else {
            if (Mode == 2) {
              Mode = 0;
            }
          }
        }
      }
    }
    buttonState = val1;
  }
  if (Mode == 0) {
    digitalWrite(FAN_PIN, HIGH);
    digitalWrite(LED_PIN, LOW);
  }
  if (Mode == 1) {
    digitalWrite(FAN_PIN, LOW);
    digitalWrite(LED_PIN, HIGH);
  }
  if (Mode == 2) { // both off
    digitalWrite(FAN_PIN, LOW);
    digitalWrite(LED_PIN, LOW);
  }
}

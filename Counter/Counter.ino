#define PIN 2

int pinValue = 0;
int previous;
int counter = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(PIN, INPUT);
  Serial.begin(9600);

  previous = digitalRead(PIN);
}


void loop() {
  pinValue = digitalRead(PIN);
  if (pinValue != previous){
    counter++;
    Serial.println(counter);
  }
  previous == pinValue;
}

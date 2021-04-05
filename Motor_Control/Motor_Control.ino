// Code to rotate motor from 0 to 100% in 30 seconds in both directions

#define FORWARDPIN 9
#define REVERSEPIN 10

void setup() {
  // Set pins as output
  pinMode(FORWARDPIN, OUTPUT);
  pinMode(REVERSEPIN, OUTPUT);

  // Turn off motor - Initial State
  digitalWrite(FORWARDPIN, LOW);
  digitalWrite(REVERSEPIN, LOW);
}

void loop() {
  // Forward
  for (float motorValue = 0; motorValue <= 1023; motorValue += 34.1){
    digitalWrite(REVERSEPIN, LOW);
    analogWrite(FORWARDPIN, motorValue);
    delay(1000);
  }
  // Reverse
  for (float motorValue = 0; motorValue <= 1023; motorValue += 34.1){
    digitalWrite(FORWARDPIN, LOW);
    analogWrite(REVERSEPIN, motorValue);
    delay(1000);
  }

}

#define POT_PIN 0   // select the input pin for the potentiometer
#define LED_PIN 5   // select the pin for the LED
int val = 0; // variable to store the value coming from the sensor


void setup()
{
  pinMode(LED_PIN, OUTPUT); // declare the LED pin as an OUTPUT
  pinMode(POT_PIN, INPUT);  // declare the potentiometer pin as an INPUT
  Serial.begin(9600);
}


void loop() 
{
  val = analogRead(POT_PIN); // read the voltage on the pot
  digitalWrite(LED_PIN, HIGH); // turn the ledPin on
  delay(val); // blink rate set by pot value (in milliseconds)
  digitalWrite(LED_PIN, LOW); // turn the ledPin off
  delay(val); // turn led off for same period as it was turned on
  Serial.println(val);
}

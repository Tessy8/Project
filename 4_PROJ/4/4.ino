#define FAN_PIN 9     //fan is connected to pwm pin 9 of the arduino
#define POT_PIN A0    // potentiometer is connected to pin A0

void setup() {
 // initialize serial communication at 9600 bits per second:
 Serial.begin(9600);
 pinMode(FAN_PIN, OUTPUT);  //define pinmode for pin 9 as OUTPUT
 pinMode(POT_PIN, INPUT);   // define potentiometer pin as INPUT
}

void loop() {
 // read the input on analog pin 0:
 int pot = analogRead(POT_PIN); 
 
 int fan_speed = pot * (255 / 1023.0); //this scales the value between 0-255
 analogWrite(FAN_PIN,fan_speed); //this sends pwm pulse to pin 9 of fan_speed no
 
 Serial.println(fan_speed); //this prints fanspeed value in serial
 delay(10); // delay of 10 to provide stability
}

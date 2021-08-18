/*
  ReadAnalogVoltage

  Reads an analog input on pin 0, converts it to voltage, and prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/ReadAnalogVoltage
*/

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  // Set pin 13 as output
  pinMode(13, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0 and pin 2:
  int sensorValue1 = analogRead(A0);
  int sensorValue2 = analogRead(A2);
  
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage1 = sensorValue1 * (5.0 / 1023.0);
  float voltage2 = sensorValue2 * (5.0 / 1023.0);

  // Get the maximum of the two potentiometer readings
  float maxVal = max(voltage1, voltage2);
  
  // print out the maximum value:
  Serial.println(maxVal);

  if (voltage1 > voltage2){
    digitalWrite(13, HIGH);
  }else if (voltage1 < voltage2){
    digitalWrite(13, LOW);
  }
}

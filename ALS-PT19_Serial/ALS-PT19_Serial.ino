void setup() 
{
  // initialize serial communication
  Serial.begin(115200);
  while (!Serial) {
        delay(100);
    }
  Serial.println("ALS-PT19 Analog Light Sensor");
}
 
 
void loop() 
{
  // read the ALS-PT19 Analog Light Sensor on analog pin 0:
  int sensorValue = analogRead(A0);
  // print out the value you read:
  Serial.print("ALS-PT19 Value: ");
  Serial.println(sensorValue);
  Serial.println("");
  delay(500);        // delay in between reads for stability
}

#include <LiquidCrystal.h>
#define CURRENT_PIN A0
#define MIN_CURRENT 1
#define MAX_CURRENT 10

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

int sensitivity = 66;
int adcValue= 0;
int offsetVoltage = 2500;
double adcVoltage = 0;
double currentValue = 0;
 
void setup() 
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print(" Motor Fault ");
  lcd.setCursor(0, 1);
  lcd.print("   Detector ");
  delay(1000);
}
 
void loop(){
  // Measure Current
  adcValue = analogRead(CURRENT_PIN);
  adcVoltage = (adcValue / 1024.0) * 5000;
  currentValue = ((adcVoltage - offsetVoltage) / sensitivity);
  
  Serial.print("Raw Sensor Value = " );
  Serial.print(adcValue);
  Serial.println("Current = ");
  Serial.print(currentValue, 3);
  lcd.clear();
  
  //LCD Display
  lcd.setCursor(0, 0);
  lcd.print("Current =       ");
  lcd.setCursor(10, 0);
  lcd.print(currentValue, 2);
  lcd.setCursor(14, 0);
  lcd.print("A");

  // Detect fault
  if (abs(currentValue) > MIN_CURRENT && abs(currentValue) < MAX_CURRENT){
    lcd.setCursor(0, 1);
    lcd.print("Motor works"); // Motor works in clockwise or counterclockwise direction
  }else if (abs(currentValue) < MIN_CURRENT){
    lcd.setCursor(0, 1);
    lcd.print("Motor is off");
  }else if (abs(currentValue) > MAX_CURRENT){
    lcd.setCursor(0, 1);
    lcd.print("Too much current");
  }
}

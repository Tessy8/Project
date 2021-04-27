#include<MFRC522.h>
#include<LiquidCrystal.h>
#include<SPI.h>

// LCD pins
#define rs 2
#define en 3
#define d4 4
#define d5 5
#define d6 6
#define d7 7

// MFRC522 pins
#define SS_PIN 10
#define RST_PIN 9

// Potentiometer pin
#define POT_PIN 8

// LED pin
#define LED_PIN 11

// Instance of the class
MFRC522 mfrc522(SS_PIN,RST_PIN);
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);

// Variables
int potValue;
int temp;

// Array to store uid and temperature
String uid_arr[10];
float temp_arr[10];

int counter = 0;

// Lower and upper limit of temperature
float LOWER_LIMIT = 36.5;
float UPPER_LIMIT = 38;

void setup()
{
  // Initialize SPI bus
  SPI.begin();

  // Set potentiometer pin as input
  pinMode(POT_PIN, INPUT);

  // Set LED pin as output
  pinMode(LED_PIN, OUTPUT);

  // Initialize LCD
  lcd.begin(16,2);

  // Initialize mfrc522
  mfrc522.PCD_Init();
}

void loop()
{
  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
  if(!mfrc522.PICC_IsNewCardPresent())
  {
    lcd.clear();
    lcd.print("Please scan your tag");
    delay(100);
    return;
  }
  
  // Verify if the NUID has been read
  if(!mfrc522.PICC_ReadCardSerial())
  {
    return;
  }

  // Read UID and store
  String uid="";
  for(int i=0;i<mfrc522.uid.size;i++)
  {
    uid.concat(String(mfrc522.uid.uidByte[i]<0x10 ? "0" : ""));
    uid.concat(String(mfrc522.uid.uidByte[i],HEX));
  }
  uid.toUpperCase();

  // Read temperature value
  potValue = analogRead(POT_PIN);
  temp = map(potValue, 0, 1023, 25, 45);

  // Print temperature value to LCD
  lcd.clear();
  lcd.print("Temp: ");
  lcd.print(temp);
  delay(2000);

  // Store UIDs and temperature values in the array
  if (counter > 9){
    uid_arr[0] = uid_arr[1];
    uid_arr[1] = uid_arr[2];
    uid_arr[2] = uid_arr[3];
    uid_arr[3] = uid_arr[4];
    uid_arr[4] = uid_arr[5];
    uid_arr[5] = uid_arr[6];
    uid_arr[6] = uid_arr[7];
    uid_arr[7] = uid_arr[8];
    uid_arr[8] = uid_arr[9];
    uid_arr[9] = uid;

    temp_arr[0] = temp_arr[1];
    temp_arr[1] = temp_arr[2];
    temp_arr[2] = temp_arr[3];
    temp_arr[3] = temp_arr[4];
    temp_arr[4] = temp_arr[5];
    temp_arr[5] = temp_arr[6];
    temp_arr[6] = temp_arr[7];
    temp_arr[7] = temp_arr[8];
    temp_arr[8] = temp_arr[9];
    temp_arr[9] = temp;
    
  }else{
    uid_arr[counter] = uid;
    temp_arr[counter] = temp;
  }

  // Turn LED on depending on temperature value
  if (temp >= LOWER_LIMIT && temp <= UPPER_LIMIT){
    digitalWrite(LED_PIN, HIGH);
    delay(1000);
    digitalWrite(LED_PIN, LOW);
  }
  
  lcd.clear();
  lcd.print("Please scan your tag");
  counter++;
}

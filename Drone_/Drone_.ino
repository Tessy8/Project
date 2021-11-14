#include <SD.h>
#include <SoftwareSerial.h>

// Define Pins
#define SD_PIN 10
#define RX_GPS 2
#define TX_GPS 3
#define DIR_PIN 4
#define STEP_PIN 5
#define BUTTON_PIN 6


File myFile;
SoftwareSerial ss(RX_GPS, TX_GPS);

// Variables
int k=0;
unsigned int dir[227];
byte gpsData;
int btnVal;
int RANGE[5] = {0.1, 0.2, 0.3, 0.4, 0.5};

void setup()
{
  Serial.begin(9600);
  ss.begin(9600);

  // Set pins as output or input
  pinMode(RX_GPS, INPUT);
  pinMode(TX_GPS, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  Serial.print("Initializing SD card...");


  if (!SD.begin(SD_PIN)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  // Read from SD card
  myFile = SD.open("file.txt");
  if (myFile) {
    while (myFile.available()) {
      int val = myFile.parseInt();
      Serial.println(val);
      dir[k]={val};
      k++;
    }
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening file.txt");
  }
}

void loop()
{
  btnVal = digitalRead(BUTTON_PIN);
  Serial.println(btnVal);
  if (btnVal == LOW){
    digitalWrite(DIR_PIN, HIGH);
    digitalWrite(STEP_PIN, HIGH);
    delay(5000);
    digitalWrite(STEP_PIN, LOW);
  }else
  {
    while (ss.available() > 0){
      gpsData = ss.read();
      Serial.println(gpsData);
      for (int i = 0; i < sizeof(dir); i++){
        if (gpsData == (dir[i] + RANGE[0]) || gpsData == (dir[i] - RANGE[0]) || gpsData == (dir[i] + RANGE[1]) || gpsData == (dir[i] - RANGE[1]) || gpsData == (dir[i] + RANGE[2]) || gpsData == (dir[i] - RANGE[2]) || gpsData == (dir[i] + RANGE[3]) || gpsData == (dir[i] - RANGE[3]) || gpsData == (dir[i] + RANGE[4]) || gpsData == (dir[i] - RANGE[4])){
          // Set motor direction clockwise and rotate for 5 seconds
          digitalWrite(DIR_PIN, HIGH);
          digitalWrite(STEP_PIN, HIGH);
          delay(5000);
          digitalWrite(STEP_PIN, LOW);
        }
      }
    }
    
  }
  
  
  }



// PROBLEM - dir[i] contains the lat, long, time and other stuffs (say just lat and long)
// gpsdata contains a very long info so you have to find a way to get the lat and long from the data and compare it with the lat and long in dir
// Also, there has to be a range
// ...

#include <HX711.h>
#include <Wire.h>
#include <RTClib.h>
#include <SoftwareSerial.h>

//Create software serial object to communicate with SIM800L
SoftwareSerial mySerial(3, 2); //SIM800L Tx & Rx is connected to Arduino #3 & #2


RTC_DS3231 rtc;
HX711 scale;

#define KY_PIN 10
#define CALIBRATION_FACTOR -7050.0 //This value is obtained using the Calibration sketch

#define LOADCELL_DOUT_PIN  5
#define LOADCELL_SCK_PIN  4

float weight;
String humidityStr;
String tempStr;
String dataSMS;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
byte rcvByte[5];  // array to store temp. and humidity values



void setup()
{
  Serial.begin(9600); // initialize serial interface
  //Begin serial communication with Arduino and SIM800L
  mySerial.begin(9600);
  pinMode(KY_PIN, OUTPUT);  // set KY_PIN mode to output
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(CALIBRATION_FACTOR); //This value is obtained by using the Calibration sketch
  scale.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0

  if (! rtc.begin()) {
    // If RTC is not found
    while (1);
  }

  if (rtc.lostPower()) {
    // If RTC loses power, set the time again  
    // Comment out below lines once you set the date & time.
    // Following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  
    // Following line sets the RTC with an explicit date & time
    // for example to set January 27 2017 at 12:56 you would call:
    // rtc.adjust(DateTime(2017, 1, 27, 12, 56, 0));
  }
  
   
}



void loop()
{
  // get data from KY-015 module
  dht();

  weight = (scale.get_units(), 1); //scale.get_units() returns a float in lbs

  // Humidity and Temperature values
  humidityStr = String(rcvByte[0], DEC) + "." + String(rcvByte[1], DEC);
  tempStr = String(rcvByte[2], DEC) + "." + String(rcvByte[3], DEC);
  

  DateTime now = rtc.now();
  if ((now.hour() == 10 && now.minute() == 0 && now.second() == 0) || (now.hour() == 16 && now.minute() == 0 && now.second() == 0) || (now.hour() == 22 && now.minute() == 0 && now.second() == 0) || (now.hour() == 4 && now.minute() == 0 && now.second() == 0)){
    mySerial.print("AT+CMGF=1\r");          // Set the shield to SMS mode
    mySerial.print("AT+CMGS=\"+***********\"\r");  //Your phone number don't forget to include your country code example +212xxxxxxxxx"
    
    dataSMS = "At " + String(now.hour()) + ":00, the temperature is " + tempStr + "degC, the humidity is " + humidityStr + "% and the weight is " + String(weight, 1) + "lbs. ";
    mySerial.print(dataSMS);  //This string is sent as SMS
    mySerial.print((char)26);//(required according to the datasheet)
    
  }
   
  delay(1000);
}



// function to get bit response from ky-015
byte get_value()
{
  byte i = 0;
  byte value = 0;
  for (i = 0; i < 8; i++) {
    while (digitalRead(KY_PIN) == LOW); // wait for KY_PIN state to be HIGH
    delayMicroseconds(30);          // wait 30 microSeconds
    if (digitalRead(KY_PIN) == HIGH)
      value |= (1 << (8 - i));      // save bit value if KY_PIN is HIGH
    while (digitalRead(KY_PIN) == HIGH); // wait for KY_PIN state to be LOW
  }
  return value;
}

// function to get temperature and humidity values from ky-015
void dht()
{
  digitalWrite(KY_PIN, LOW);  // set KY_PIN LOW to start communication with module
  delay(30);              // wait 30 milliSeconds
  digitalWrite(KY_PIN, HIGH); // set KY_PIN HIGH
  delayMicroseconds(40);  // wait 40 microSeconds
  pinMode(KY_PIN, INPUT);     // change KY_PIN mode to input
  while (digitalRead(KY_PIN) == HIGH);    // wait for pin to be LOW
  delayMicroseconds(80);  // wait for 80 microSeconds

  if (digitalRead(KY_PIN) == LOW)
    delayMicroseconds(80); // wait for 80 microSeconds
  for (int i = 0; i < 5; i++) // receive temperature and humidity values
    rcvByte[i] = get_value();
  pinMode(KY_PIN, OUTPUT);    // change KY_PIN mode to ouptut
  digitalWrite(KY_PIN, HIGH); // set KY_PIN to HIGH
}

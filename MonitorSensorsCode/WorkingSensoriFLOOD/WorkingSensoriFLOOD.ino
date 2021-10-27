// Flood Hazard Research Lab - Mayfly 2.0
// This code make readings between a specific time interval in minutes
// (average of 12 readings in 2 seconds),
// records Temperature, Battery Voltage and Water Level (NAV83) with 
// Ultrasonic Sensor (HRXL-MaxSonar-WRLT and I2CLX-MaxSonar-WR/WRC)onto the microSD card.

// Send data via GPRSbee->Hologram->AWS four times a day, at 00:00, 06:00, 12:00, 18:00 UTC

// Standard Libraries
#include <Wire.h>
#include <avr/sleep.h>
#include <avr/wdt.h>
#include <SPI.h>
#include <SD.h>

// SODAQ Libraries
#include <RTCTimer.h>
#include <Sodaq_DS3231.h>
#include <Sodaq_PcInt_PCINT0.h>       // Sodaq_PcInt Modified (check EnviroDIY)

// Ultrasonic Sensor
#include <SoftwareSerial_PCINT12.h>   // SoftwareSerial Modified (check EnviroDIY)

// GPRSbee
#include <GPRSbee.h>

// Data Record
String dateTimeRec;

// Board Temperature
float boardtemp = 0.0;

// Battery Voltage
int batteryPin = A6;        // input pin for the potentiometer
int batterysenseValue = 0;  // variable to store the value coming from the sensor
float batteryvoltage;       // Battery Voltage value after calculation

// Ultrasonic Sensor (HRXL-MaxSonar-WRLT, tested with MB7386)
const int SonarExcite = 10;                // ultrasonic sensor power pin is connected to pin D10 (yellow wire)
const int dataPin = 11;                    // data pin is connected to D11 (white wire)
SoftwareSerial sonarSerial(dataPin, -1);      
boolean stringComplete = false;
int rangeHRXL;               // Variable to store the range coming from ultrasonic sensor HRXL-MaxSonar-WRLT
const int minHRXL = 500;     // Minimum range detection in mm (identify wl error)
const int maxHRXL = 9000;    // Maximum 

int range;
const int numReadings = 10;
int total = 0;
int readIndex = 0;
int average = 0;

// Ultrasonic Sensor (I2CLX-MaxSonar-WR/WRC, tested with MB7040)
int rangeI2CLX;              // Variable to store the range coming from ultrasonic sensor I2CLX-MaxSonar-WR/WRC
const int minI2CLX = 0;      // Maximum range detection in cm (identify wl error)
const int maxI2CLX = 764;    // Maximum  

// Water Level convertion
float elevref1 = 2.35;       // elevation in meters, referenced with NAV83 vertical Datum (Sonar 1)
float elevref2 = 2.29;       // elevation in meters, referenced with NAV83 vertical Datum (Sonar 2) - not updated
float wlHRXL = 0.000;        // water level (NAV83) read by HRXL sensor
float wlI2CLX = 0.00;        // water level (NAV83) read by I2CLX sensor

// GPRSbee
int BEE_DTR_PIN = 23;   // Bee DTR Pin (Data Terminal Ready - used for sleep)
int BEE_CTS_PIN = 19;   // Bee CTS Pin (Clear to Send)
String pubRec = "SN180050\n"; //CHANGE THESE WHEN TESTING
String boardSN = "180050"; //CHANGE THESE WHEN TESTING

#define READ_DELAY 1

// RTC Timer
RTCTimer timer;

String dataRec = "";
int currentminute;
int currenthour;
long currentepochtime = 0;
int readInterval = 6;    // SET the interval between readings in minutes
int sendInterval = 6;    // SET sending data interval in hours

// RTC Interrupt pin
#define RTC_PIN A7
#define RTC_INT_PERIOD EveryMinute

// Digital pin 12 is the MicroSD slave select pin on the Mayfly
#define SD_SS_PIN 12

//The data log file
#define FILE_NAME "SN180050.txt"            // -G: 8.3 format 12345678.TXT or .LOG

//Data header
#define DATA_HEADER "DateTime,BoardTemp(C),Battery(V),RangeHRXL(mm),WLHRXL(m),RangeI2CLX(cm),WLI2CLX(m)"

// GPRSbee
#define APN "hologram"  // fill APN
#define URL "http://d3uyjvsgi4dmwc.cloudfront.net/prod/mayflyupload" // URL to do HTTP POST

void setup() 
{
  // Initialise the serial connection
  Serial.begin(57600);              // Start serial port for display
  sonarSerial.begin(9600);          // Start serial port for maxSonar
  rtc.begin();
  delay(100);
  pinMode(8, OUTPUT);               // Set Green LED as output
  pinMode(9, OUTPUT);               // Set Red LED as output
  pinMode(SonarExcite, OUTPUT);     // Set ultrasonic sensor power pin as output
  digitalWrite(SonarExcite, LOW);   // pin 10 is the power pin for the ultrasonic sensor

  //GPRSbee
  delay(500);
  Serial1.begin(9600);              // Start serial port for GPRSbee
  gprsbee.init(Serial1, BEE_CTS_PIN, BEE_DTR_PIN);
  gprsbee.setPowerSwitchedOnOff(true);
  gprsbee.off();

  // Blink the LEDs to show the board is ON
  greenred4flash();

  // Initialise log file
  setupLogFile();

  // Setup timer events
  setupTimer();
  
  // Setup sleep mode
  setupSleep();
  
  Serial.print("Power On, running: Flood Hazard Research Lab - Mayfly 1 - S/N ");
  Serial.print(boardSN);
  Serial.println(" - Mayfly_Sonar21.ino");
  Serial.println(DATA_HEADER);  
}


void loop() 
{   
  // Update the timer 
  timer.update();
  
  if(currentminute % readInterval == 0) //if the time ends in an even number, a sample will be taken. Can be changed to other intervals
     {   
          greenred4flash();
          
          // Create the data record
          dataRec = createDataRecord();
    
          // Save the data record to the log file
          logData(dataRec);
 
          // Echo the data to the serial connection
          Serial.println(dataRec);      
      
          dataRec = "";   


          // Create the data record to be published
          pubRec += createPubRecord();
          Serial.println(pubRec);
       
          // Send data when it is time
          if(currenthour % sendInterval == 0)
             {
                 if(currentminute == 00)
                    { 
                        digitalWrite(8, HIGH);
                        const char* pubRec1 = pubRec.c_str();
                        const char* postData = pubRec1;
                        Serial.print(sizeof(postData));
                        Serial.println(postData);
                        char buffer[50];            
                        memset(buffer, 0, sizeof(buffer));
                        bool retval = gprsbee.doHTTPPOSTWithReply(APN, URL, postData, strlen(postData), buffer, sizeof(buffer));
                          if (retval)
                          {
                             Serial.print(("HTTP Post result: "));
                             Serial.println(buffer);
                             pubRec = "SN";
                             pubRec += boardSN;
                             pubRec += "\n";             // Clear pubRec for next period
                          }
                    }
             }       
     }
      
  systemSleep();
}


void sendPubRec()
{

}

void showTime(uint32_t ts)
{
  // Retrieve and display the current date/time
  String dateTime = getDateTime();
  //Serial.println(dateTime);
}

void setupTimer()
{
  // Schedule the wakeup every minute
  timer.every(READ_DELAY, showTime);
  
  // Instruct the RTCTimer how to get the current time reading
  timer.setNowCallback(getNow);
}

void wakeISR()
{
  //Leave this blank
}

void setupSleep()
{
  pinMode(RTC_PIN, INPUT_PULLUP);
  PcInt::attachInterrupt(RTC_PIN, wakeISR);

  //Setup the RTC in interrupt mode
  rtc.enableInterrupts(RTC_INT_PERIOD);
  
  //Set the sleep mode
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
}

void systemSleep()
{  
  // Wait until the serial ports have finished transmitting
  Serial.flush();
  Serial1.flush();
  
  // The next timed interrupt will not be sent until this is cleared
  rtc.clearINTStatus();
    
  // Disable ADC
  ADCSRA &= ~_BV(ADEN);
  
  // Sleep time
  noInterrupts();
  sleep_enable();
  interrupts();
  sleep_cpu();
  sleep_disable();
 
  // Enbale ADC
  ADCSRA |= _BV(ADEN); 
}

String getDateTime()
{
  String dateTimeStr;
  
  // Create a DateTime object from the current time
  DateTime dt(rtc.makeDateTime(rtc.now().getEpoch()));

  currentepochtime = (dt.get());    //Unix time in seconds 

  currentminute = (dt.minute());

  currenthour = (dt.hour());
  
  // Convert it to a String
  dt.addToString(dateTimeStr); 
  return dateTimeStr;  
}

uint32_t getNow()
{
  currentepochtime = rtc.now().getEpoch();
  return currentepochtime;
}

void greenred4flash()
{
  for (int i=1; i <= 4; i++){
  digitalWrite(8, HIGH);   
  digitalWrite(9, LOW);
  delay(50);
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  delay(50);
  }
  digitalWrite(9, LOW);
}

void setupLogFile()
{
  // Initialise the SD card
  if (!SD.begin(SD_SS_PIN))
  {
    Serial.println("Error: SD card failed to initialise or is missing.");
    //Hang
    //while (true); 
  }
  
  // Check if the file already exists
  bool oldFile = SD.exists(FILE_NAME);  
  
  // Open the file in write mode
  File logFile = SD.open(FILE_NAME, FILE_WRITE);
  
  // Add header information if the file did not already exist
  if (!oldFile)
  {
    //logFile.println(LOGGERNAME);
    logFile.println(DATA_HEADER);
  }
  
  // Close the file to save it
  logFile.close();  
}

void logData(String rec)
{
  // Re-open the file
  File logFile = SD.open(FILE_NAME, FILE_WRITE);
  
  // Write the CSV data
  logFile.println(rec);
  
  // Close the file to save it
  logFile.close();  
}

String createDataRecord()
{
    // Create a String type data record in csv format
    // DateTime,BoardTemp(C),Battery(V),RangeHRXL(mm),WLHRXL(m),RangeI2CLX(cm),WLI2CLX(m)
    
    dateTimeRec = getDateTime();
    String data =  dateTimeRec + ",";
    
    // Board Temperature
    rtc.convertTemperature();          // convert current temperature into registers
    boardtemp = rtc.getTemperature();  // read temperature sensor value

    // Battery Voltage
    batterysenseValue = analogRead(batteryPin);               // read Battery Sense Value in Input Analog Pin
    batteryvoltage = (3.3/1023.) * 4.47 * batterysenseValue;  // calculate Battery Voltage (for Mayfly v0.5 and newer)

    // Ultrasonic Sensor (HRXL-MaxSonar-WRLT)
    delay(500);    
    digitalWrite(8, HIGH);
    digitalWrite(SonarExcite, HIGH);
    delay(1000);
    
    readIndex = 0;
    do {
      digitalWrite(9, HIGH);
      range = SonarHRXLRead();
      digitalWrite(9, LOW);
      
      if(stringComplete){
        stringComplete = false;

        total = total + range;
        readIndex = readIndex + 1;

        Serial.print("Reading: ");
        Serial.print(readIndex);
        Serial.print(", ");
        Serial.print(range);
        Serial.print(" mm, ");
        Serial.println(total);

        delay(150);        
      }
    } while(readIndex < 10);

    average = total / numReadings;
    Serial.print("Average MB7386 = ");
    Serial.println(average);
    
    rangeHRXL = average;
    //rangeHRXL = SonarHRXLRead();
    wlHRXL = elevref1 - (float(rangeHRXL)/1000);

    total = 0;
    readIndex = 0;
    average = 0;
    
    digitalWrite(SonarExcite, LOW);
    digitalWrite(8, LOW);

    // Ultrasonic Sensor (I2CXL-MaxSonar-WR/WRC)
    delay(1000);
    digitalWrite(9, HIGH);
    delay(1000);
    
     readIndex = 0;
     do {
      digitalWrite(8, HIGH);
      range = SonarI2CLXRead();
      digitalWrite(8, LOW);   

      total = total + range;
      readIndex = readIndex + 1;

        Serial.print("Reading: ");
        Serial.print(readIndex);
        Serial.print(", ");
        Serial.print(range);
        Serial.print(" cm, ");
        Serial.println(total);

        delay(150);    

     } while(readIndex < 10);

     average = total / numReadings;
     Serial.print("Average MB7040 = ");
     Serial.println(average);

     rangeI2CLX = average;
     //rangeI2CLX = SonarI2CLXRead();
     wlI2CLX = elevref2 - (float(rangeI2CLX)/100);

     total = 0;
     readIndex = 0;
     average = 0;
    
     digitalWrite(9, LOW);        

    // Loggertime
    //data += currentepochtime;
    //data += ",";
    
    // Add readings to data
    addFloatToString(data, boardtemp, 3, 1);
    data += ",";

    addFloatToString(data, batteryvoltage, 4, 2);
    data += ",";

    data += String(rangeHRXL);
    data += ",";
    // If there is a sensor reading error, write -9999 as water level
    if (rangeHRXL < minHRXL)  // Don't accept negative value for range        
    {
      wlHRXL = -9999;         
      addFloatToString(data, wlHRXL, 4, 0);
    }   
    else if (rangeHRXL > maxHRXL)  // Check if is out of range
    {
      wlHRXL = -9999;
      addFloatToString(data, wlHRXL, 4, 0);
    }
    else
    {
      addFloatToString(data, wlHRXL, 3, 2); 
    }
    data += ",";
    stringComplete = false;

    data += String(rangeI2CLX);
    data += ",";
    //     If there is a sensor reading error, write -9999 as water level
    if (rangeI2CLX < minI2CLX)  // Don't accept negative value for range        
    {
      wlI2CLX = -9999;         
      addFloatToString(data, wlI2CLX, 4, 0);
    }   
    else if (rangeI2CLX > maxI2CLX)  // Check if is out of range
    {
      wlI2CLX = -9999;
      addFloatToString(data, wlI2CLX, 4, 0);
    }
    else
    {
      addFloatToString(data, wlI2CLX, 3, 2);  
    }
  
    return data;
}


String createPubRecord()
{
    // Create a String type data record to be published

    String dataPub = dateTimeRec;
    dataPub += ",";

    // Ultrasonic Sensor (HRXL-MaxSonar-WRLT)
    if (rangeHRXL < minHRXL)  // Don't accept negative value for range        
    {
      wlHRXL = -9999;         
      addFloatToString(dataPub, wlHRXL, 4, 0);
    }   
    else if (rangeHRXL > maxHRXL)  // Check if is out of range
    {
      wlHRXL = -9999;
      addFloatToString(dataPub, wlHRXL, 4, 0);
    }
    else
    {
      addFloatToString(dataPub, wlHRXL, 3, 2); 
    }

    dataPub += ",";

    // Ultrasonic Sensor (I2CXL-MaxSonar-WR/WRC)
    if (rangeI2CLX < minI2CLX)  // Don't accept negative value for range        
    {
      wlI2CLX = -9999;         
      addFloatToString(dataPub, wlI2CLX, 4, 0);
    }   
    else if (rangeI2CLX > maxI2CLX)  // Check if is out of range
    {
      wlI2CLX = -9999;
      addFloatToString(dataPub, wlI2CLX, 4, 0);
    }
    else
    {
      addFloatToString(dataPub, wlI2CLX, 3, 2);  
    }
    dataPub += "\n";
    
    return dataPub;
}

static void addFloatToString(String & str, float val, char width, unsigned char precision)
{
  char buffer[10];
  dtostrf(val, width, precision, buffer);
  str += buffer;
}

int SonarHRXLRead() 
{
  int result;
  char inData[5];                                          // char array to read data into
  int index = 0;

  while (sonarSerial.read() != -1) {}
   
  while (stringComplete == false) {

      if (sonarSerial.available())
    {
      char rByte = sonarSerial.read();                     // read serial input for "R" to mark start of data
      if(rByte == 'R')
      {
        //Serial.println("rByte set");
        while (index < 4)                                  // read next three character for range from sensor
        {
          if (sonarSerial.available())
          {
            inData[index] = sonarSerial.read(); 
            //Serial.println(inData[index]);               // Debug line

            index++;                                       // Increment where to write next
          }  
        }
        inData[index] = 0x00;                              // add a padding byte at end for atoi() function
      }

      rByte = 0;                                           // reset the rByte ready for next reading

      index = 0;                                           // reset index ready for next reading
      stringComplete = true;                               // set completion of read to true
      result = atoi(inData);                               // changes string data into an integer for use
    }
  } 

  return result;
}

int SonarI2CLXRead()
{
  int reading;
  
  // Step 1: Take a range reading
  Wire.beginTransmission(112);      // take a single reading and save for the next range request
                                    // Default Address: 112 for the I2CXL-MaxSonar-WR/WRC (7-bit addressing scheme)
  Wire.write(byte(0x00));           // sets register pointer to the command register (0x00);
  Wire.write(byte(0x51));           // command sensor measure unit: (0x50) for inches | (0x51) for centimeters
                                    // (0x52) for ping microseconds
  Wire.endTransmission();           // stop transmitting
  // Step 2: Interval between readings to allow for propor acoustic dissipation
  delay(100);                       // datasheet suggests at least 100 milliseconds
  // Step 3: Instruct sensor to return a particular echo reading
  Wire.beginTransmission(112);      // transmit to device #112
  Wire.write(byte(0x02));           // sets register pointer to echo #1 register (0x02)
  Wire.endTransmission();           // stop transmitting
  // Step 4: Request reading from sensor
  Wire.requestFrom(112, 2);         // request 2 bytes from slave device #112
  // Step 5: Receive reading from sensor
  if (2 <= Wire.available()) {      // if two bytes were received
    reading = Wire.read();          // receive high byte (overwrites previous reading)
    reading = reading << 8;         // shift high byte to be high 8 bits
    reading |= Wire.read();         // receive low byte as lower 8 bits
    //Serial.println(reading);      // print the reading
  }

  return reading;
}

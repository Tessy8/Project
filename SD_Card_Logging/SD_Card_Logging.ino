//Libraries
#include <SD.h>
#include <SPI.h>
#include <DHT.h>;
#include <OneWire.h>
#include <DallasTemperature.h>

// Pins
#define ONE_WIRE_BUS_1 5
#define ONE_WIRE_BUS_2 6
#define ONE_WIRE_BUS_3 8
#define ONE_WIRE_BUS_4 9
#define DHTPIN 7 
#define SENSOR_PIN1 A0
#define SENSOR_PIN2 A1
#define SENSOR_PIN3 A2
#define SENSOR_PIN4 A3
#define CS_pin 10

#define DHTTYPE DHT22   // DHT 22  (AM2302)


//// Initialize DHT sensor for normal 16mhz Arduino
DHT dht(DHTPIN, DHTTYPE); 

OneWire oneWire1(ONE_WIRE_BUS_1);
OneWire oneWire2(ONE_WIRE_BUS_2);
OneWire oneWire3(ONE_WIRE_BUS_3);
OneWire oneWire4(ONE_WIRE_BUS_4);

DallasTemperature sensors1(&oneWire1);
DallasTemperature sensors2(&oneWire2);
DallasTemperature sensors3(&oneWire3);
DallasTemperature sensors4(&oneWire4);


File sdcard_file;

// Constants
float hum;
float temp;  
float output;
float Celsius1 = 0;
float Fahrenheit1 = 0;
float Celsius2 = 0;
float Fahrenheit2 = 0;
float Celsius3 = 0;
float Fahrenheit3 = 0;
float Celsius4 = 0;
float Fahrenheit4 = 0;


void setup() {
  Serial.begin(9600);
  pinMode(SENSOR_PIN1,INPUT);
  pinMode(SENSOR_PIN2,INPUT);
  pinMode(SENSOR_PIN3,INPUT);
  pinMode(SENSOR_PIN4,INPUT);
  pinMode(CS_pin, OUTPUT);
  dht.begin();
  sensors1.begin();
  sensors2.begin();
  sensors3.begin();
  sensors4.begin();
  
  
  // SD Card Initialization
  if (SD.begin())
  {
    Serial.println("SD card is ready to use.");
  } else
  {
    Serial.println("SD card initialization failed");
    return;
  }

  
  sdcard_file = SD.open("data.txt", FILE_WRITE);
  if (sdcard_file) { 
    sdcard_file.print("Start "); 
    sdcard_file.close(); // close the file
  }
  // if the file didn't open, print an error:
  else {
    Serial.println("error opening test.txt");
  }
}

void DHT_(){
  //Read data and store it to variables hum and temp
  hum = dht.readHumidity();
  temp= dht.readTemperature();
  //Print temp and humidity values to serial monitor
  Serial.print("Humidity: ");
  Serial.print(hum);
  Serial.print(" %, Temp: ");
  Serial.print(temp);
  Serial.println(" Celsius");

  // Store temp and humidity values to SD card
  sdcard_file = SD.open("data.txt", FILE_WRITE);
  if (sdcard_file) {    
    sdcard_file.print("Humidity: ");
    sdcard_file.print(hum);   
    sdcard_file.print(" %, Temp: ");
    sdcard_file.print(temp);
    sdcard_file.println(" Celsius");
    sdcard_file.close(); // close the file
  }
  // if the file didn't open, print an error:
  else {
    Serial.println("error opening test.txt");
  }
}

void DS18B20_1(){
  sensors1.requestTemperatures(); 
  Celsius1=sensors1.getTempCByIndex(0);
  Fahrenheit1=sensors1.toFahrenheit(Celsius1);
  Serial.print(" C  ");
  Serial.print(Celsius1);
  Serial.print(" F  ");
  Serial.println(Fahrenheit1);

  // Store temp values to SD card
  sdcard_file = SD.open("data.txt", FILE_WRITE);
  if (sdcard_file) {    
    sdcard_file.print("Temp from DS18B20_1: ");
    sdcard_file.print(Celsius1);   
    sdcard_file.print(" degree Celsius OR ");
    sdcard_file.print(Fahrenheit1);
    sdcard_file.println(" Fahrenheit");
    sdcard_file.close(); // close the file
  }
  // if the file didn't open, print an error:
  else {
    Serial.println("error opening test.txt");
  }
}


void DS18B20_2(){
  sensors2.requestTemperatures(); 
  Celsius2=sensors2.getTempCByIndex(0);
  Fahrenheit2=sensors2.toFahrenheit(Celsius2);
  Serial.print(" C  ");
  Serial.print(Celsius2);
  Serial.print(" F  ");
  Serial.println(Fahrenheit2);

  // Store temp values to SD card
  sdcard_file = SD.open("data.txt", FILE_WRITE);
  if (sdcard_file) {    
    sdcard_file.print("Temp from DS18B20: ");
    sdcard_file.print(Celsius2);   
    sdcard_file.print(" degree Celsius OR ");
    sdcard_file.print(Fahrenheit2);
    sdcard_file.println(" Fahrenheit");
    sdcard_file.close(); // close the file
  }
  // if the file didn't open, print an error:
  else {
    Serial.println("error opening test.txt");
  }
}



void DS18B20_3(){
  sensors3.requestTemperatures(); 
  Celsius3=sensors3.getTempCByIndex(0);
  Fahrenheit3=sensors3.toFahrenheit(Celsius3);
  Serial.print(" C  ");
  Serial.print(Celsius3);
  Serial.print(" F  ");
  Serial.println(Fahrenheit3);

  // Store temp values to SD card
  sdcard_file = SD.open("data.txt", FILE_WRITE);
  if (sdcard_file) {    
    sdcard_file.print("Temp from DS18B20: ");
    sdcard_file.print(Celsius3);   
    sdcard_file.print(" degree Celsius OR ");
    sdcard_file.print(Fahrenheit3);
    sdcard_file.println(" Fahrenheit");
    sdcard_file.close(); // close the file
  }
  // if the file didn't open, print an error:
  else {
    Serial.println("error opening test.txt");
  }
}


void DS18B20_4(){
  sensors4.requestTemperatures(); 
  Celsius4=sensors4.getTempCByIndex(0);
  Fahrenheit4=sensors4.toFahrenheit(Celsius4);
  Serial.print(" C  ");
  Serial.print(Celsius4);
  Serial.print(" F  ");
  Serial.println(Fahrenheit4);

  // Store temp values to SD card
  sdcard_file = SD.open("data.txt", FILE_WRITE);
  if (sdcard_file) {    
    sdcard_file.print("Temp from DS18B20: ");
    sdcard_file.print(Celsius4);   
    sdcard_file.print(" degree Celsius OR ");
    sdcard_file.print(Fahrenheit4);
    sdcard_file.println(" Fahrenheit");
    sdcard_file.close(); // close the file
  }
  // if the file didn't open, print an error:
  else {
    Serial.println("error opening test.txt");
  }
}




void loop() {
  DS18B20_1();
  DS18B20_2();
  DS18B20_3();
  DS18B20_4();
  DHT_();
  delay(5000);
}
  

    

#include <SensirionI2CScd4x.h>
#include <Wire.h>
#include <Adafruit_LPS2X.h>
#include <Adafruit_Sensor.h>

// For SPI mode, we need a CS pin
#define LPS_CS 10
// For software-SPI mode we need SCK/MOSI/MISO pins
#define LPS_SCK 13
#define LPS_MISO 12
#define LPS_MOSI 11

Adafruit_LPS22 lps;
SensirionI2CScd4x scd4x;


void setup() {

    Serial.begin(115200);
    while (!Serial) {
        delay(100);
    }

    Wire.begin();

    uint16_t error;
    char errorMessage[256];

    scd4x.begin(Wire);

    // stop potentially previously started measurement
    error = scd4x.stopPeriodicMeasurement();
    if (error) {
        Serial.print("Error trying to execute stopPeriodicMeasurement(): ");
        errorToString(error, errorMessage, 256);
        Serial.println(errorMessage);
    }


    // Try to initialize!
  if (!lps.begin_I2C()) {
  //if (!lps.begin_SPI(LPS_CS)) {
  //if (!lps.begin_SPI(LPS_CS, LPS_SCK, LPS_MISO, LPS_MOSI)) {
    Serial.println("Failed to find LPS22 chip");
    while (1) { delay(10); }
  }
  Serial.println("LPS22 Found!");

  lps.setDataRate(LPS22_RATE_10_HZ);
  Serial.print("Data rate for LPS22 set to: ");
  switch (lps.getDataRate()) {
    case LPS22_RATE_ONE_SHOT: Serial.println("One Shot / Power Down"); break;
    case LPS22_RATE_1_HZ: Serial.println("1 Hz"); break;
    case LPS22_RATE_10_HZ: Serial.println("10 Hz"); break;
    case LPS22_RATE_25_HZ: Serial.println("25 Hz"); break;
    case LPS22_RATE_50_HZ: Serial.println("50 Hz"); break;

  }

    Serial.println("Waiting for first measurement... ");
}

void loop() {
    uint16_t error;
    char errorMessage[256];

    // Read Measurement
    uint16_t co2;
    float tempe;
    float humid;
    int sensorValue = analogRead(A0);
    sensors_event_t temp;
    sensors_event_t pressure;
    
    error = scd4x.readMeasurement(co2, tempe, humid);
    if (error) {
        Serial.print("Error trying to execute readMeasurement(): ");
        errorToString(error, errorMessage, 256);
        Serial.print("Error for SCD4X is ");
        Serial.println(errorMessage);
    } else if (co2 == 0) {
        Serial.println("Invalid sample detected, skipping.");
    } else {
        Serial.println("For SCD4X-");
        Serial.print("Co2: ");
        Serial.println(co2);
        Serial.print("Temperature: ");
        Serial.println(tempe); 
        Serial.print("Humidity: ");
        Serial.println(humid);
    }

    lps.getEvent(&pressure, &temp);// get pressure
    Serial.println("For LPS22-");
    Serial.print("Temperature: ");
    Serial.print(temp.temperature);
    Serial.println(" degrees C");
    Serial.print("Pressure: ");
    Serial.print(pressure.pressure);
    Serial.println(" hPa");
    Serial.println("");

    Serial.print("ALS-PT19 Value: ");
    Serial.println(sensorValue);
  
    delay(5000);
}

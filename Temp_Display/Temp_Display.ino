/*
 * Connect Signal pin of DHT11 to pin 2
 * Place a 10 K ohm resistor between VCC and the data pin, 
 * to act as a medium-strength pull up on the data line. 
 * 
 * For TFT, connect:
 * LED (backlight)     to   Vcc (3.3v)
 * 2 SCK (slave clock) to   D13
 * 3 SDA (MOSI)        to   D4
 * 4 A0  (DC)          to   D9
 * 5 RESET             to   D8
 * 6 CS (SS)           to   D10
 * 7 Gnd               to   Gnd
 * 8 Vcc               to  Vcc (3.3v)
 */

#include "DHT.h"
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7735

// Define Pin Numbers
#define TFT_CS        10
#define TFT_RST        8
#define TFT_DC         9
#define DHTPIN         2    

// DHT 11 Object
#define DHTTYPE DHT11   

// Initialize DHT and TFT sensor
DHT dht(DHTPIN, DHTTYPE);
// For 1.14", 1.3", 1.54", and 2.0" TFT with ST7789:
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);



void setup() {
  // put your setup code here, to run once:
  dht.begin();
  tft.init(240, 240, SPI_MODE3);               // Init ST7789 240x240
  tft.setRotation(2);
  //  pinMode(TFT_BACKLIGHT, OUTPUT);
  //digitalWrite(TFT_BACKLIGHT, HIGH); // Backlight on

  tft.fillScreen(ST77XX_BLACK);
  testdrawtext("Welcome... ", "");
}

void loop() {
  // put your main code here, to run repeatedly:
  // Read Humidity 
   float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    testdrawtext("Reading...", "");
    return;
  }

  String hum = String(h) + "%" ;
  String temp = String(t) + "C";
    
  testdrawtext("Humidity:", hum);
  testdrawtext("Temperature:", temp);

  delay(2000);
}


void testdrawtext(String text, String value) {

  //tft.setTextWrap(false);
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0, 0);
  tft.setTextColor(ST77XX_RED);
  tft.setTextSize(1.5);
  tft.setTextWrap(true);
  tft.print(text);
  tft.setCursor(1, 0);
  tft.print(value);
}

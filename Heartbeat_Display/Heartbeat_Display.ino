/*
 * Connect Signal pin of KY039HS to pin A0 
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
 

#define USE_ARDUINO_INTERRUPTS true    // Set-up low-level interrupts for most acurate BPM math.

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7735
#include <PulseSensorPlayground.h>     // Includes the PulseSensorPlayground Library.   


// Define Pin Numbers
#define TFT_CS        10
#define TFT_RST        8
#define TFT_DC         9    
   

// For 1.14", 1.3", 1.54", and 2.0" TFT with ST7789:
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);
PulseSensorPlayground pulseSensor;  // Creates an instance of the PulseSensorPlayground object called "pulseSensor"


// Variables
const int PulseWire = 0;       // PulseSensor PURPLE WIRE connected to ANALOG PIN 0
int Threshold = 550;           // Determine which Signal to "count as a beat" and which to ignore.



void setup() {
  // put your setup code here, to run once:
  tft.init(240, 240, SPI_MODE3);               // Init ST7789 240x240
  tft.setRotation(2);
  //  pinMode(TFT_BACKLIGHT, OUTPUT);
  //digitalWrite(TFT_BACKLIGHT, HIGH); // Backlight on

  tft.fillScreen(ST77XX_BLACK);
  testdrawtext("Welcome... ", "");

  // Configure the PulseSensor object, by assigning our variables to it. 
  pulseSensor.analogInput(PulseWire);   
  pulseSensor.setThreshold(Threshold);   

  // Double-check the "pulseSensor" object was created and "began" seeing a signal. 
   if (pulseSensor.begin()) {
    testdrawtext("Reading...", "");
    }
}

void loop() {
  // put your main code here, to run repeatedly:
  int myBPM = pulseSensor.getBeatsPerMinute();  // Calls function on our pulseSensor object that returns BPM as an "int".

  String hb = String(myBPM);
  if (pulseSensor.sawStartOfBeat()) {            // Constantly test to see if "a beat happened". 
   testdrawtext("♥ BPM: ", hb);
  }
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

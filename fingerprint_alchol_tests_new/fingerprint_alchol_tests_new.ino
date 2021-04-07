#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7735
#include <SPI.h>


#if defined(ARDUINO_FEATHER_ESP32)
#define TFT_CS         14
#define TFT_RST        15
#define TFT_DC         32

#elif defined(ESP8266)
#define TFT_CS         4
#define TFT_RST        16
#define TFT_DC         5

#else

#define TFT_CS        10
#define TFT_RST        8
#define TFT_DC         9
#endif


// For 1.14", 1.3", 1.54", and 2.0" TFT with ST7789:
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);




int content = 0;
String name = "";

#include <Adafruit_Fingerprint.h>

#define mySerial Serial1


Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

void setup()
{
  Serial.begin(9600);
  while (!Serial);
  delay(100);
  Serial.println("\n\nAdafruit finger detect test");

  // set the data rate for the sensor serial port
  finger.begin(57600);

  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1) {
      delay(1);
    }
  }
  tft.init(240, 240, SPI_MODE3);               // Init ST7789 240x240
  tft.setRotation(2);
  //  pinMode(TFT_BACKLIGHT, OUTPUT);
  //digitalWrite(TFT_BACKLIGHT, HIGH); // Backlight on

  Serial.println(F("Initialized"));

  uint16_t time = millis();
  tft.fillScreen(ST77XX_BLACK);
  time = millis() - time;

  Serial.println(time, DEC);
  delay(500);

  finger.getTemplateCount();
  Serial.print("Sensor contains "); Serial.print(finger.templateCount); Serial.println(" templates");
  Serial.println("Waiting for valid finger...");
  testdrawtext("welcome to the test...... ");
  delay(5000);

}

void loop() {
  testdrawtext("place your finger on the scanner ");
  delay(2000);
  getFingerprintID();
  delay(50);            //don't ned to run this at full speed.
}

uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No finger detected");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK success!

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK converted!
  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Found a print match!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("Did not find a match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }

  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID);
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  getId(finger.fingerID);
  return finger.fingerID;
}

// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;

  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID);
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  getId(finger.fingerID);
  return finger.fingerID;
}

void testdrawtext(String text) {

  //tft.setTextWrap(false);
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0, 0);
  tft.setTextColor(ST77XX_RED);
  tft.setTextSize(2);
  tft.setTextWrap(true);
  tft.print(text);
}
void breathe (String name) {
  testdrawtext("welcome" + (name) + "please blow into the reader ");
  delay(2000);

  for ( int i = 0; i < 10; i++) {
    content = analogRead(A0);
    Serial.print("alcohol senced: ");
    Serial.println(content);
    testdrawtext("analyzing alchol content in your  breathe" );
    delay(700);
  }
  testdrawtext("DONE YOU CAN STEP AWAY NOW");  //5 seconds
  delay(2000);
  if (content > 500) {
    testdrawtext("you are drunk content is : " + String(content));
    delay(3000);
    testdrawtext("sorry you cant work today " );
  } else {
    testdrawtext("good breathe content is" + String(content));
    delay(3000);
    testdrawtext("go inside you can work today");
  }
}
void getId(int id) {

  switch (id) {
    case 1: name = "Steve"; break;
    case 2: name = "Anthony"; break;

  }
  Serial.print("Hello ");
  Serial.println(name);
  breathe(name);

}

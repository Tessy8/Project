#define BLYNK_PRINT Serial
#define PIN 3
#define VIRTUALPIN V5
#define BLYNK_MAX_SENDBYTES 1200

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "YourAuthToken";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "YourNetworkName";
char pass[] = "YourPassword";

BLYNK_READ(VIRTUALPIN){
  if (digitalRead(PIN) == 0){
    Blynk.virtualWrite(VIRTUALPIN, "OFF");
  }else if (digitalRead(PIN == 1){
    Blynk.virtualWrite(VIRTUALPIN, "ON");
  }
}

BLYNK_CONNECTED(){
   Blynk.syncAll();  //to send the latest values of all values
}

void setup()
{
  Blynk.begin(auth, ssid, pass);
  // Wifi.begin(ssid, pass);
}

void loop()
{
  Blynk.run(); 
}

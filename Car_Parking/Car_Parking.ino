#include <WiFi.h>
#include <WiFiMulti.h>

WiFiMulti wifiMulti;

//1. Change the following info
const char* ssid     = "Yourssid"; // Your SSID (Name of your WiFi)
const char* password = "Wifipass"; //Your Wifi password

const char* host = "api.thingspeak.com";
String api_key = "APIKEY"; // Your API Key provied by thingspeak

#define ID 01                 // ID of device
#define LED 0                 // spot occupancy signal
#define carState 6            // IR pin

String str = "";
int countYes = 0;
   

void setup() {
  delay(1000);
  Serial.begin (9600);     // serial debugging
  pinMode(LED, OUTPUT);         // spot indication
  pinMode(carState, INPUT);     // ir as input

  Connect_to_Wifi();
}

void loop() {

  int carStateChange = digitalRead(carState);      // read ir input
  if (carStateChange == HIGH) {                     // if high then count and send data
    countYes++;                             //increment count
    if ((countYes % 2) == 0){
      Serial.print("Car has entered " ); 
      Serial.println(countYes );
      Serial.println(" times");
      digitalWrite(LED, LOW);
      
      // Use WiFiClient class to create TCP connections
      WiFiClient client;
      const int httpPort = 80;
      
      if (!client.connect(host, httpPort)) {
        Serial.println("connection failed");
        return;
      }else{
        str = String("Parking Space ") + String(ID) + String(" is occupied");
        client.print("POST /update HTTP/1.1\n");
        client.print("Host: api.thingspeak.com\n");
        client.print("Connection: close\n");
        client.print("X-THINGSPEAKAPIKEY: " + api_key + "\n");
        client.print("Content-Type: application/x-www-form-urlencoded\n");
        client.print("Content-Length: ");
        client.print(str.length());
        client.print("\n\n");
        client.print(str);
      }
    }else{
      Serial.print("Car has exited " ); 
      Serial.println(countYes);
      Serial.println(" times");
      digitalWrite(LED, HIGH);
      // Use WiFiClient class to create TCP connections
      WiFiClient client;
      const int httpPort = 80;
      
      if (!client.connect(host, httpPort)) {
        Serial.println("connection failed");
        return;
      }else{
        str = String("Parking Space ") + String(ID) + String(" is available");
        client.print("POST /update HTTP/1.1\n");
        client.print("Host: api.thingspeak.com\n");
        client.print("Connection: close\n");
        client.print("X-THINGSPEAKAPIKEY: " + api_key + "\n");
        client.print("Content-Type: application/x-www-form-urlencoded\n");
        client.print("Content-Length: ");
        client.print(str.length());
        client.print("\n\n");
        client.print(str);
      }
    }
  }
  delay(5000);
}

void Connect_to_Wifi()
{

  // We start by connecting to a WiFi network
  wifiMulti.addAP(ssid, password);

  Serial.println();
  Serial.println();
  Serial.print("Wait for WiFi... ");

  while (wifiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

}

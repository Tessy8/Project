/*    STUDENT NUMBER:
 *    TIME STARTED:
 * 
 *    GUIDANCE:
 *    This program includes a class to simulate a simple  MQTT library. Hence, there is no requirement for an internet connection.
 *        
 *    The MQQT library requires the following actions from yourself.
 *    1) Change the #define USERNAME  "JOEBLOGGS" with your actual username/student ID.
 *    2) Call the .initMQQT class method in setup() and pass your username. Hint: offlineMQQT.initMQQT(USERNAME);
 *    3) Use the publishMQQT method to simulate sending data over MQQT. 
 *    Reference:
 *    class method: publishMQQT ( char feed[], char message[]  )
 *    feed is a pointer to char data type with the feed name (char array string). 
 *    message is a pointer to char containing the actual message (char array string).
 *    
 *    Good luck!
 *    
 */

// Include RFID, SPI, Wire, Grove RGB LCD and OLDE library
#include <MFRC522.h>
#include <SPI.h>
#include <Wire.h>
#include <rgb_lcd.h>

#define USERNAME  "JOEBLOGGS" // replace with your username

// Define pins
#define SS_PIN 0
#define RST_PIN 2
#define LED_PIN 15
#define LDR_PIN A0


// Instance of the class
MFRC522 rfid(SS_PIN, RST_PIN); 
rgb_lcd lcd;

// State to check if cat is in or out
int previousState = 1; // Cat is inside at power up

// Status of LDR
int ldrStatus;

// Count number of times cat has entered and left
int out = 0;
int in = 0;

/* You do not need to do anything to this class */
class offlineMQQT 
{
   char i_username[80];
  
   public:
   void initMQQT ( char username[] )
   {
      strcpy(i_username,username);
   }
   
   void publishMQQT ( char feed[], char message[]  )
   {
      Serial.println("");
      Serial.print("Sending message to account username: ");
      Serial.println(i_username);
      Serial.print("Message:");
      Serial.println(message);
   }
  
};

offlineMQQT offlineMQQT; // do not change this either

void setup()                  // the setup function is called once on startup
{
  
  Serial.begin(115200);       // initialise serial, for communication with the host pc
  while (!Serial)             // while the serial port is not ready
  {
    ;                         // do nothing
  }
  delay(500);
  Serial.println(""); Serial.println(""); Serial.println(""); // print three empty lines to seperate ASCII chars generated during start up.

  // Initialize SPI bus
  SPI.begin();

  // Initialize LCD and set background color to green
  lcd.begin(16, 2);
  lcd.setRGB(0, 255, 0);

  // Initialize RFID
  rfid.PCD_Init();  

  // Set LED pin as output
  pinMode(LED_PIN, OUTPUT);

  // Set LDR pin as input
  pinMode(LDR_PIN, INPUT);
   
  // Clear the buffer.

}

void loop() 
{
  checkRFID();
  displayCounts();
  delay(100);
}


void checkRFID(){
  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
  if(!rfid.PICC_IsNewCardPresent())
  {
    return;
  }
  
  // Verify if the NUID has been read
  if(!rfid.PICC_ReadCardSerial())
  {
    return;
  }

  // Check if pet is inside or outside
  if (previousState == 1){
    // Add to the number of times cat has left the property
    out++;

    // Set LCD backlight red
    lcd.setRGB(255, 0, 0); // Red
    
    // Illuminate LCD yellow if pet tries to leave when dark
    ldrStatus = analogRead(LDR_PIN);
    if (ldrStatus <= 300){
      lcd.setRGB(255, 255, 0); // Yellow
      delay(1000);
      lcd.setRGB(255, 0, 0); // Red
    }
        
    previousState = 0;
  }
  else if (previousState == 0){
    // Add to the number of times cat has entered the property
    in++;

    // Set LCD backlight green
    lcd.setRGB(0, 255, 0); // Green
    
    previousState = 1;
  }

  // Turn LED on for 5 seconds
  digitalWrite(LED_PIN, HIGH);
  delay(5000);
  digitalWrite(LED_PIN, LOW);
}

void displayCounts(){
  lcd.clear();
  lcd.noBlink();
  lcd.setCursor(0,0);
  lcd.print("Entered: ");
  lcd.print(in);
  lcd.setCursor(0,1);
  lcd.print("Exited: ");
  lcd.print(out);
}

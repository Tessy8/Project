//  Define IR sensor pins
#define IR_SENSOR_ENTRY 11
#define IR_SENSOR_EXIT 12

// Define LED pins
#define LED_RED_1 5
#define LED_RED_2 4
#define LED_GREEN_3 3
#define LED_GREEN_4 2

// Define Buzzer pin
#define BUZZER_PIN 8

//L293D
//Motor A
#define MOTOR_PIN_1 6  // Pin 14 of L293
#define MOTOR_PIN_2 7  // Pin 10 of L293
//Motor B
#define MOTOR_PIN_3 10 // Pin  7 of L293
#define MOTOR_PIN_4 9  // Pin  2 of L293

// Define Limit Switches Pin
#define LIMIT_1 0   // For bridge close
#define LIMIT_2 1   // For bridge open

// Variables for reading from IR sensors
int IRSensorExit;
int IRSensorEntry;

// Variables for reading from limit switches
int pos_close;    // For bridge close
int pos_open;     // For bridge open


void setup() 
{
  pinMode(IR_SENSOR_ENTRY, INPUT);
  pinMode(IR_SENSOR_EXIT, INPUT);
  pinMode(LED_RED_1, OUTPUT);
  pinMode(LED_RED_2, OUTPUT);
  pinMode(LED_GREEN_3, OUTPUT);
  pinMode(LED_GREEN_4, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(MOTOR_PIN_1, OUTPUT);
  pinMode(MOTOR_PIN_2, OUTPUT);
  pinMode(MOTOR_PIN_3, OUTPUT);
  pinMode(MOTOR_PIN_4, OUTPUT);
  pinMode(LIMIT_1, OUTPUT);
  pinMode(LIMIT_2, OUTPUT);
  
}
void loop() {
  // Read the IR Sensors
  IRSensorEntry = digitalRead(IR_SENSOR_ENTRY);
  IRSensorExit = digitalRead(IR_SENSOR_EXIT);
  
  if (IRSensorEntry == HIGH)
  { 
    // Turn red LEDs on, green LEDs off and buzzer on
    digitalWrite(LED_RED_1, LOW);
    digitalWrite(LED_RED_2, LOW);
    digitalWrite(LED_GREEN_3, HIGH);
    digitalWrite(LED_GREEN_4, HIGH);
    digitalWrite(BUZZER_PIN, LOW);

    // Close the bridge
    pos_close = digitalRead(LIMIT_1);
    if (pos_close == LOW){
      digitalWrite(MOTOR_PIN_1, HIGH);
      digitalWrite(MOTOR_PIN_2, LOW);
      digitalWrite(MOTOR_PIN_3, HIGH);
      digitalWrite(MOTOR_PIN_4, LOW);
      
    }else if (pos_close == HIGH){
      digitalWrite(MOTOR_PIN_1, LOW);
      digitalWrite(MOTOR_PIN_2, LOW);
      digitalWrite(MOTOR_PIN_3, LOW);
      digitalWrite(MOTOR_PIN_4, LOW);
      
    }
    
  }
  else if (IRSensorExit == LOW && IRSensorEntry == LOW)
  {
    
    // Open the bridge
    pos_open = digitalRead(LIMIT_2);
    if (pos_open == LOW){
      digitalWrite(MOTOR_PIN_1, LOW);
      digitalWrite(MOTOR_PIN_2, HIGH);
      digitalWrite(MOTOR_PIN_3, LOW);
      digitalWrite(MOTOR_PIN_4, HIGH);
      
    }else if (pos_open == HIGH){
      digitalWrite(MOTOR_PIN_1, LOW);
      digitalWrite(MOTOR_PIN_2, LOW);
      digitalWrite(MOTOR_PIN_3, LOW);
      digitalWrite(MOTOR_PIN_4, LOW);
      
    }

    // Turn red LEDs off, green LEDs on and buzzer off
    digitalWrite(LED_RED_1, HIGH);
    digitalWrite(LED_RED_2, HIGH);
    digitalWrite(LED_GREEN_3, LOW);
    digitalWrite(LED_GREEN_4, LOW);
    digitalWrite(BUZZER_PIN, HIGH);

  }
  delay(200);
}

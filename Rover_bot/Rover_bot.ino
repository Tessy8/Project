// Ultrasonic sensor pins
#define TRIG1 53
#define ECHO1 52
#define TRIG2 51
#define ECHO2 50
#define TRIG3 49
#define ECHO3 48
#define TRIG4 47
#define ECHO4 46
#define TRIG5 45
#define ECHO5 44
#define TRIG6 43
#define ECHO6 42
#define TRIG7 41
#define ECHO7 40
#define TRIG8 39
#define ECHO8 38
#define TRIG9 37
#define ECHO9 36
#define TRIG10 35
#define ECHO10 34
#define TRIG11 33
#define ECHO11 32
#define TRIG12 31
#define ECHO12 30
#define TRIG13 29
#define ECHO13 28
#define TRIG14 27
#define ECHO14 26
#define TRIG15 25
#define ECHO15 24
#define TRIG16 23
#define ECHO16 22

// define variables for distance measurement
float distance1; 
float distance2; 
float distance3; 
float distance4; 
float distance5; 
float distance6; 
float distance7; 
float distance8; 
float distance9; 
float distance10; 
float distance11; 
float distance12; 
float distance13; 
float distance14; 
float distance15; 
float distance16; 

// define variables
int trigPin;
int echoPin;
long duration;
float distance;


void setup() {
  // Set TRIG pins as output
  for (int i = 53; i >= 22; i-=2){
    pinMode(i, OUTPUT);
  }
  // Set ECHO pins as input
  for (int j = 52; j >= 22; j-=2){
    pinMode(j, INPUT);
  }
}

float dist(int trigPin, int echoPin){
  // Clear the TRIG pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Set the TRIG pin active for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the ECHO pin
  duration = pulseIn(echoPin, HIGH);

  // Calculate the distance
  distance = duration * 0.034 / 2;
  return distance;
}

void loop() {
  // Get distance
  distance1 = dist(TRIG1, ECHO1);
  distance2 = dist(TRIG2, ECHO2);
  distance3 = dist(TRIG3, ECHO3);
  distance4 = dist(TRIG4, ECHO4);
  distance5 = dist(TRIG5, ECHO5);
  distance6 = dist(TRIG6, ECHO6);
  distance7 = dist(TRIG7, ECHO7);
  distance8 = dist(TRIG8, ECHO8);
  distance9 = dist(TRIG9, ECHO9);
  distance10 = dist(TRIG10, ECHO10);
  distance11 = dist(TRIG11, ECHO11);
  distance12 = dist(TRIG12, ECHO12);
  distance13 = dist(TRIG13, ECHO13);
  distance14 = dist(TRIG14, ECHO14);
  distance15 = dist(TRIG15, ECHO15);
  distance16 = dist(TRIG16, ECHO16);
  
}

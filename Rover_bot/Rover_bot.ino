// Ultrasonic sensor pins
// Front
#define TRIG1 53
#define ECHO1 52
#define TRIG2 51
#define ECHO2 50
#define TRIG3 49
#define ECHO3 48
#define TRIG4 47
#define ECHO4 46
// Back
#define TRIG5 45
#define ECHO5 44
#define TRIG6 43
#define ECHO6 42
#define TRIG7 41
#define ECHO7 40
#define TRIG8 39
#define ECHO8 38
// Right
#define TRIG9 37
#define ECHO9 36
#define TRIG10 35
#define ECHO10 34
#define TRIG11 33
#define ECHO11 32
#define TRIG12 31
#define ECHO12 30
// Left
#define TRIG13 29
#define ECHO13 28
#define TRIG14 27
#define ECHO14 26
#define TRIG15 25
#define ECHO15 24
#define TRIG16 23
#define ECHO16 22

// Motor pins
#define LEFTFORWARD 2
#define LEFTBACKWARD 3
#define RIGHTFORWARD 4
#define RIGHTBACKWARD 5
#define ENABLE12 6
#define ENABLE34 7

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

// define variables for average
float avg1;
float avg2;
float avg3;
float avg4;

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
  // Set MOTOR pins as output
  pinMode(LEFTFORWARD, OUTPUT);
  pinMode(LEFTBACKWARD, OUTPUT);
  pinMode(RIGHTFORWARD, OUTPUT);
  pinMode(RIGHTBACKWARD, OUTPUT);
  pinMode(ENABLE12, OUTPUT);
  pinMode(ENABLE34, OUTPUT);

  // Turn off motors - Initial State
  digitalWrite(LEFTFORWARD, LOW);
  digitalWrite(LEFTBACKWARD, LOW);
  digitalWrite(RIGHTFORWARD, LOW);
  digitalWrite(RIGHTBACKWARD, LOW);
  digitalWrite(ENABLE12, LOW);
  digitalWrite(ENABLE34, LOW);
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

  avg1 = avg(distance1, distance2, distance3, distance4);     // Front
  avg2 = avg(distance5, distance6, distance7, distance8);     // Back
  avg3 = avg(distance9, distance10, distance11, distance12);  // Right
  avg4 = avg(distance13, distance14, distance15, distance16); // Left
  
  // Enable the motors
  digitalWrite(ENABLE12, HIGH);
  digitalWrite(ENABLE34, HIGH);

  // Move forward
  if (avg1 > 10){
    forward();
  }else{
    float num = maxNumber(avg1, avg2, avg3, avg4);         // Maximum of the numbers
    if (num == avg1 && avg1 > 10){
      // Continue moving
      forward();
    }else if (num == avg2 && avg2 > 10){
      // Turn 180 degrees
      back();
      // then move forward
      forward();
    }else if (num == avg3 && avg3 > 10){
      //Turn to the right
      right();
      // then move forward
      forward();
    }else if (num == avg4 && avg4 > 10){
      //Turn to the left
      left();
      // then move forward
      forward();
    }else{
      // Stop
      halt();
    }
  }
}


// Function to calculate distance
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

// Function to calculate average of distances
float avg(float dist1, float dist2, float dist3,float dist4){
  float mean = (dist1 + dist2 + dist3 + dist4)/4;
  return mean;
}

// Function to calculate maximum of three numbers
float maxNumber(float first, float secnd, float third, float fourth){
  float maxNum = max(first, secnd);
  maxNum = max(maxNum, third);
  maxNum = max(maxNum, fourth);
  return maxNum;
}

// Function for robot to move forward
void forward(){
  digitalWrite(LEFTFORWARD, HIGH);
  digitalWrite(LEFTBACKWARD, LOW);
  digitalWrite(RIGHTFORWARD, HIGH);
  digitalWrite(RIGHTBACKWARD, LOW);  
}

// Function for robot to stop
void halt(){
  digitalWrite(LEFTFORWARD, LOW);
  digitalWrite(LEFTBACKWARD, LOW);
  digitalWrite(RIGHTFORWARD, LOW);
  digitalWrite(RIGHTBACKWARD, LOW);  
}

// Function for robot to turn left
void left(){
  digitalWrite(LEFTFORWARD, LOW);
  digitalWrite(LEFTBACKWARD, LOW);
  digitalWrite(RIGHTFORWARD, HIGH);
  digitalWrite(RIGHTBACKWARD, LOW);
  delay(3000);  
}

// Function for robot to turn right
void right(){
  digitalWrite(LEFTFORWARD, HIGH);
  digitalWrite(LEFTBACKWARD, LOW);
  digitalWrite(RIGHTFORWARD, LOW);
  digitalWrite(RIGHTBACKWARD, LOW);
  delay(3000);  
}

// Function for robot to turn to the back
void back(){
  digitalWrite(LEFTFORWARD, LOW);
  digitalWrite(LEFTBACKWARD, LOW);
  digitalWrite(RIGHTFORWARD, HIGH);
  digitalWrite(RIGHTBACKWARD, LOW);
  delay(6000);  
}

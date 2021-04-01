// Code to select between two modes at the click of a button
#define BUTTON 3
int btnValue = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(BUTTON, INPUT);
}

// Temperature loop
void temp(){
  
}

// Time loop
void time_(){
  
}

void loop() {
  // read input from button
  btnValue = digitalRead(BUTTON);
  
  switch (btnValue) {
    case 0:
      temp();
      break;
    case 1:
      time_();
      break;
}
  
}

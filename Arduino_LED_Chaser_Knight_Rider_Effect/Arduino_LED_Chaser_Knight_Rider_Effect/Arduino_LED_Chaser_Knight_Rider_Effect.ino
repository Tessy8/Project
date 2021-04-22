//5 LED Knight Rider
//Subscribe to our youtube channel , Facebook : https://www.facebook.com/tmtronics/

#define LED 7

int leds[] = {2,3,4,5,6};//Led pins , you can add more led pins here
int timer=100; //led speed
int ledState = 0;
void setup()
{
for(int i=0; i<5; i++) {
pinMode(leds[i], OUTPUT);// this line make led pins as a output
pinMode(LED, OUTPUT);
}
}
void loop()
{
  ledState = digitalRead(LED);
  if (ledState == LOW){       // Blink LEDs at 1 second interval
    digitalWrite(LED, HIGH);
  }else if (ledState == HIGH){
    digitalWrite(LED, LOW);
  }
   
  for(int i=0; i<4; i++) {    //leds on 1 to 5 (forward)
    digitalWrite(leds[i], HIGH);
    delay(timer);
    digitalWrite(leds[i], LOW);
  }
  for(int i=4; i>0; i--) {    //leds on 5 to 1 (Backward)
    digitalWrite(leds[i], HIGH);
    delay(timer);
    digitalWrite(leds[i], LOW);
  }

}

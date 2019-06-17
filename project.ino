
#include <Servo.h>

Servo esc;

#define encoder0PinA 2
#define encoder0PinB 3
#define encoder0Btn 4
int encoder0Pos = 0;
int escwaarde = 90;
int tussenwaarde;

const int ledPin =  7; 
int ledState = LOW;             // ledState used to set the LED
long previousMillis = 0; 
long interval;  

void setup() {
  esc.attach(9);
  
  Serial.begin(9600);
  pinMode(encoder0PinA, INPUT_PULLUP);
  pinMode(encoder0PinB, INPUT_PULLUP);
  pinMode(encoder0Btn, INPUT_PULLUP);
  attachInterrupt(0, doEncoder, CHANGE);
  pinMode(ledPin, OUTPUT);  
  
}
int valRotary,lastValRotary;
void loop() {
  unsigned long currentMillis = millis();
  int btn = digitalRead(encoder0Btn);

  //Serial.print(" waarde van de rem is  "); //veel prints staan in commentaar wegens de communicatie tussen pi en arduino
  //Serial.println(btn);
  //Serial.println(encoder0Pos);
  //Serial.println(valRotary);
 //Serial.print(" de waarde voor esc is ");
  //Serial.println(" ");
  //Serial.print(escwaarde);
  float waardePi = encoder0Pos /226.0 *10.0;
  if(round(waardePi) > 9)
  {
    waardePi = 9;
  }
  Serial.print(int(waardePi));
  if(btn == 1){
  if(valRotary > 0 && valRotary < 89 && valRotary != lastValRotary){
    escwaarde = 90 +valRotary;
    }
  
  lastValRotary = valRotary;
  esc.write(escwaarde);
  if(escwaarde < 101){
    interval = 700;
    }
    else{
      interval = 100;
      }
    if(currentMillis - previousMillis > interval) {
    // save the last time you blinked the LED 
    previousMillis = currentMillis;   
 
    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW){
      ledState = HIGH;
    }
    else{
      ledState = LOW;
    }
     digitalWrite(ledPin, ledState);
    }
    }
    else if(btn == 0 ){
     // Serial.println("HIJ IS NU AAN HET REMMEN");
      if(encoder0Pos <= 0){
        encoder0Pos = 0;
      }
      else
      {
        encoder0Pos--;  
      }
      valRotary = encoder0Pos/2.5;
      escwaarde = 90 +valRotary;
      esc.write(escwaarde);
      digitalWrite(ledPin, HIGH);
      }
    
    delay(100); //zet altijd terug op 100
  }
  

  
  

void doEncoder()
{
  if (digitalRead(encoder0PinA) == digitalRead(encoder0PinB))
  {
  encoder0Pos++;
  }
  else
  {
  encoder0Pos--;
  }
    if(encoder0Pos < 0){
    encoder0Pos = 0;
    }
    if(encoder0Pos > 226){  
      encoder0Pos= 226;
      }
  valRotary = encoder0Pos/2.5;

}

#include <Stepper.h>

#define STEPSIZE 25600
int PUL=7; //define Pulse pin
int DIR=6; //define Direction pin
int ENA=5; //define Enable Pin

int count = 0; //used ater for counting the number of rev
int spinDir = -1; //used in logic for changing direction of motor

void setup() {
  pinMode (PUL, OUTPUT);//set pin 7 as output pin
  pinMode (DIR, OUTPUT);//set pin 7 as output pin
  pinMode (ENA, OUTPUT);
  digitalWrite(DIR,LOW);
  digitalWrite(ENA,HIGH);

}.

void loop() {
  
    digitalWrite(PUL,HIGH);
    delayMicroseconds(100);
    digitalWrite(PUL,LOW);
    delayMicroseconds(100);
    count += 1;
    
    if(count == STEPSIZE){
       count = -STEPSIZE;
       spinDir *= -1;
       if(spinDir == 1){
         digitalWrite(DIR, HIGH);
       }
       else{
         digitalWrite(DIR, LOW);
       }
    }
      
}

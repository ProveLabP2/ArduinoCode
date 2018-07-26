#include <Stepper.h>

#define STEPSIZE 1600//Number of steps for one revolution
int PUL=7; //define Pulse pin
int DIR=6; //define Direction pin
int ENA=5; //define Enable Pin

int count = 0; //used after for counting the number of steps
int spinDir = -1; //used in logic for changing direction of motor's rotation

void setup() {
  pinMode (PUL, OUTPUT);//set pin 7 as output pin
  pinMode (DIR, OUTPUT);//set pin 6 as output pin
  pinMode (ENA, OUTPUT);//set pin 8 as output pin
  digitalWrite(DIR,LOW);//set intial direction of motor's rotation
  digitalWrite(ENA,HIGH);

}.

void loop() {
    //generate pulse
    digitalWrite(PUL,HIGH);
    delayMicroseconds(100);
    digitalWrite(PUL,LOW);
    delayMicroseconds(100);
    //increment the step count
    count += 1;
    
    if(count == STEPSIZE){
       count = -STEPSIZE;//reset count to zero
       spinDir *= -1; //used for changing the direction of the rotation

       //change the roation after each revolution
       if(spinDir == 1){
         digitalWrite(DIR, HIGH);
       }
       else{
         digitalWrite(DIR, LOW);
       }
    }
      
}

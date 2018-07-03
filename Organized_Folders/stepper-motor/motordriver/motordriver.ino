#include <Stepper.h>

#define STEPSIZE 25600 // Number of steps for one revolution
int PUL=7; //define Pulse pin
int DIR=6; //define Direction pin
int ENA=5; //define Enable Pin

int count = 0; //used ater for counting the number of steps
int spinDir = -1; //used in logic for changing direction of motor's rotation

void setup() {
  pinMode (PUL, OUTPUT);//set pin 7 as output pin
  pinMode (DIR, OUTPUT);//set pin 6 as output pin
  pinMode (ENA, OUTPUT); //set pin 5 as output pin
  digitalWrite(DIR,LOW); // set the initial direction of motor's rotation
  digitalWrite(ENA,HIGH); // set ENABLE pin

}.

void loop() {

    // Generate a pulse
    digitalWrite(PUL,HIGH); 
    delayMicroseconds(100);
    digitalWrite(PUL,LOW);
    delayMicroseconds(100);

    // Increment the step count
    count += 1;
    
    if(count == STEPSIZE){
       count = -STEPSIZE;  // Reset count to zero
       spinDir *= -1; // Used for changing the direction of rotation

       // Change the rotation after each revolution
       if(spinDir == 1){
         digitalWrite(DIR, HIGH);
       }
       else{
         digitalWrite(DIR, LOW);
       }
    }
      
}

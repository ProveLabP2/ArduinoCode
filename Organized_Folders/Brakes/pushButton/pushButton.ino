#include <Stepper.h>

#define STEPSIZE 6500 // Number of steps for one revolution, max step size for brakes
int PUL=7; //define Pulse pin
int DIR=6; //define Direction pin
int ENA=5; //define Enable Pin

int count = 0; //used ater for counting the number of steps
int state=0; //state of brake (engaged or disengaged), 0 is not engaged

// button code
int button = 8;

void setup() {
  pinMode (PUL, OUTPUT);//set pin 7 as output pin
  pinMode (DIR, OUTPUT);//set pin 6 as output pin
  pinMode (ENA, OUTPUT); //set pin 5 as output pin
  digitalWrite(DIR,LOW); // set the initial direction of motor's rotation
  digitalWrite(ENA,HIGH); // set ENABLE pin
  pinMode(button, INPUT_PULLUP); // set the internal pull up resistor, pressed button is HIGH 


}

void loop(){ 
//a) if the button is pressed the button is HIGH and brakes are engaged by setting DIR to LOW
//b) if the button is not pressed the button is LOW and the brakes are disengaged by setting DIR to HIGH

if (digitalRead(button) == HIGH && state==0) { 
    // Generate a pulse
    digitalWrite(DIR,LOW); // set direction of motor to engage brake
    count=0;
    while(count<=STEPSIZE){
    digitalWrite(PUL,HIGH); 
    delayMicroseconds(100);
    digitalWrite(PUL,LOW);
    delayMicroseconds(100);

    // Increment the step count
    count += 1;
    
    if(count == STEPSIZE){
        state=1;
    }
}
}
if (digitalRead(button) == LOW && state==1) {
    //set spin direction
    digitalWrite(DIR,HIGH);  // set direction of motor to disengage brake
    count=0; 
    // Generate a pulse
    while(count<=STEPSIZE){
    digitalWrite(PUL,HIGH); 
    delayMicroseconds(100);
    digitalWrite(PUL,LOW);
    delayMicroseconds(100);

    // Increment the step count
    count += 1;
    
    if(count == STEPSIZE){
      state=0;
    }
    }
}
}

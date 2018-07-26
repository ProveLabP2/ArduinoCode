#include <Stepper.h>

#define STEPSIZE 1600 // Number of steps for one revolution
int PUL=7; //define Pulse pin
int DIR=6; //define Direction pin
int ENA=5; //define Enable Pin

int count = 0; //used ater for counting the number of steps
int newval = 0;
int oldval = 0;
int turnval = 0;
int numsteps = 0;

const int X_pin = 0; // analog pin connected to X output
//const int Y_pin = 1; // analog pin connected to Y output


int steerval(int stickval){
    return (int)(stickval * (512 / (STEPSIZE/2)));
}

void setup() {
  pinMode (PUL, OUTPUT);//set pin 7 as output pin
  pinMode (DIR, OUTPUT);//set pin 6 as output pin
  pinMode (ENA, OUTPUT); //set pin 5 as output pin
  digitalWrite(DIR,LOW); // set the initial direction of motor's rotation
  digitalWrite(ENA,HIGH); // set ENABLE pin
  Serial.begin(9600);
}

void loop() {

 
 newval =  analogRead(X_pin);//Get the latest reading from the joystick
 Serial.print("New Joystick Value: "); // Print the info to serial
 Serial.println(newval); // Print the debug value to serial 
 
 oldval = newval; //Save the read value from the joystick
 numsteps = 0; // REset the number of steps for steering to zero
 Serial.print("Old Joystick Value: "); // Print the info to serial
 Serial.println(oldval); // Print the debug value to serial 

 // Check if there is a need for steering and determine its required direction
 if (newval > oldval){
  
    //Change the direction of the stepper motor for steering 
    digitalWrite(DIR, HIGH);
    //Compute the number of steps required for steering from the current position
    numsteps = newval - oldval;
    Serial.print("Number of turn steps for steering towards right: "); // Print the info to serial
    Serial.println(numsteps); // Print the debug value to serial
 }
 else{
  
    //Change the direction of the stepper motor for steering in other direction
    digitalWrite(DIR, LOW);
    //Compute the number of steps required for steering from the current position
    numsteps = oldval - newval;
    Serial.print("Number of turn steps for  Steering towards left: "); // Print the info to serial
    Serial.println(numsteps); // Print the debug value to serial
 }
 
 // Perform steering if the movement in the joystick it is above a certain turn threshold
 numsteps = 10; // +++ temporirly added for debug
 if (numsteps > 5){

    // Reset the count value to zero
    // count = 0; //--- temporirly commenting for debugging

    //Get the turn angle (adjusted number of steps) for steering
    turnval = steerval(numsteps);

    turnval = 256; // +++ temporirly added for debug
    
    Serial.print("Computed turnval Steering: "); // Print the info to serial
    Serial.println(turnval); // Print the debug value to serial
    
    
    //Generate pulses for the required steering
    //while (count < turnval){
      
      digitalWrite(PUL,HIGH); 
      delayMicroseconds(100);
      digitalWrite(PUL,LOW);
      delayMicroseconds(100);

      // Increment the turn/step count
      count += 1;
      Serial.print("T"); // Print the info to serial

    //}
    //turnval = count; // +++ temporirly added for debug
    // +++ temporirly added the following 3 lines for debug
    //while(1){
     // delayMicroseconds(500);
    //}
   }

}
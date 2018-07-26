#include <Stepper.h>

//const int X_pin = 0; //Analog input for x direction

#define STEPSIZE 1600 // Number of steps for one revolution
int PUL = 7; //define Pulse pin
int DIR = 6; //define Direction pin
int ENA = 5; //define Enable Pin

int count = 0; //used ater for counting the number of steps
int spinDir = -1; //used in logic for changing direction of motor's rotation
int newval = 0;
int oldval = 0;
float turnval = 0;
int numsteps = 0;

float steerval(int stickval) {
  //return (stickval * (512 / (STEPSIZE / 2)));
  return (stickval * (STEPSIZE / 1024));
}

const int X_pin = 0; // analog pin connected to X output
const int Y_pin = 1; // analog pin connected to Y output

void setup() {
  pinMode (PUL, OUTPUT);//set pin 7 as output pin
  pinMode (DIR, OUTPUT);//set pin 6 as output pin
  pinMode (ENA, OUTPUT); //set pin 5 as output pin
  digitalWrite(DIR, LOW); // set the initial direction of motor's rotation
  digitalWrite(ENA, LOW); // set ENABLE pin to low for disabling the motor
  Serial.begin(9600);
}

void loop() {

  newval =  analogRead(X_pin);//Get the latest reading from the joystick
  numsteps = 0;

  if (oldval != newval) {
    
    Serial.print("New Joystick Value: "); // Print the info to serial
    Serial.println(newval); // Print the debug value to serial 

    Serial.print("Old Joystick Value: "); // Print the info to serial
    Serial.println(oldval); // Print the debug value to serial 

    
    if (newval > oldval) {

      //Change the direction of the stepper motor for steering
      digitalWrite(DIR, HIGH);
      //Compute the number of steps required for steering from the current position
      numsteps = newval - oldval;
      Serial.print("Number of turn steps for steering towards right: "); // Print the info to serial
      Serial.println(numsteps); // Print the debug value to serial
    }
    else {
      

      //Change the direction of the stepper motor for steering in other direction
      digitalWrite(DIR, LOW);
      //Compute the number of steps required for steering from the current position
      numsteps = oldval - newval;
      Serial.print("Number of turn steps for  Steering towards left: "); // Print the info to serial
      Serial.println(numsteps); // Print the debug value to serial
    }

    oldval = newval; //Save the read value from the joystick
  }


  if (numsteps > 0) {

    // Reset the count value to zero
    count = 0;
    // Reset the turnval value to zero
    turnval = 0;

    //Get the turn angle (adjusted number of steps) for steering
    //turnval = round(steerval(numsteps));
    turnval = map(numsteps, 0, 1023, 0, STEPSIZE);
    
    Serial.print("Computed turnval Steering: "); // Print the info to serial
    Serial.println(turnval); // Print the debug value to serial

    if (turnval > 0){
      digitalWrite(ENA, HIGH); // set ENABLE pin to HIGH for enabling the motor
    }
    
    
    //Generate pulses for the required steering
    while (count < turnval) {
      
      digitalWrite(PUL, HIGH);
      delayMicroseconds(100);
      digitalWrite(PUL, LOW);
      delayMicroseconds(100);

      // Increment the step count
      count += 1;

    }
    digitalWrite(ENA, LOW); // set ENABLE pin to LOW for disabling the motor

  }

  delay(500);
}

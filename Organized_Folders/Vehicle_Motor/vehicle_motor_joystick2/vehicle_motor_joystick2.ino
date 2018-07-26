//const int X_pin = 0; // analog pin connected to X output (Currently not used)
const int Y_pin = 1; // analog pin connected to Y output

volatile int readval=0;//for reading the joystick value
volatile int validrange = 0; //valid range for the speed control
volatile int speedval = 0; //for setting the speed

void setup() {

  pinMode(6,OUTPUT);// pin 6 is output (yellow wire on arduino)
  Serial.begin(9600); // Initialize serial 

}

void loop() {

  Serial.print("JoyStick Reading: "); // Print info to serial
  readval = analogRead(Y_pin); // Read the Y value from the joystick
  
  validrange = constrain (readval, 540, 1023);
  Serial.println(validrange); // print the value read from joystick to serialv
  
  // If the value is greater than resting/center value of the joystick then change the speed
  if (validrange >  540) {

    speedval = map(validrange,512,1023,0,255);
    
    Serial.print("Speed Value: "); // Print the info to serial
    Serial.println(speedval); // Print the computed speed value to serial 
    analogWrite(6, speedval); //Compute and set  the speed so that the value is between 0 and 255
   // delay(500); // Set Delay

  }
  else {
  // if the joystick is at resting position or moved in the other direction, then speed is set to zero
    analogWrite(6, 0);  // Set the speed to zero
   // delay(500); // Set Delay
  }

 
  delay(100); //set delay
}

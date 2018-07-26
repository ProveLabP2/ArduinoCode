const int X_pin = 0; // analog pin connected to X output (Currently not used)
const int Y_pin = 1; // analog pin connected to Y output

volatile int i=0;//initializing a integer for incrementing and decrementing duty ratio.

void setup() {

  //pinMode(6,OUTPUT);// pin 6 is output (yellow wire on arduino)
  Serial.begin(9600); // Initialize serial 

}

void loop() {

  Serial.print("JoyStick Reading: "); // Print info to serial
  i = analogRead(Y_pin); // Read the Y value from the joystick
  Serial.println(i); // print the value read from joystick to serial
  
  // If the value is less than resting/center value of the joystick then change the speed
  if (i < 512) {

    
    //analogWrite(6, (256 - i/2)); //Compute and set  the speed so that the value is between 0 and 255
    analogWrite(6, 100);
    Serial.print("Speed Value: "); // Print the info to serial
    Serial.println(i/2); // Print the computed speed value to serial 
    delay(500); // Set Delay

  }
  else {
  // if the joystick is at resting position or moved in the other direction, then speed is set to zero
    analogWrite(6, 0);  // Set the speed to zero
    delay(500); // Set Delay
  }

 

}

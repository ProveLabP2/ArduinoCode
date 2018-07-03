#include <SoftwareSerial.h>

SoftwareSerial mySerial(4, 5); //RX, TX

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
}


void loop() {
  
  if(Serial.available() > 0){//Read from serial monitor and send over HC-12
    Serial.println("Sending: "); 
    String input = Serial.readString();
    mySerial.println(input);   
    Serial.println(input); 
  }
 
  if(mySerial.available() > 1){//Read from HC-12 and send to serial monitor
    Serial.println("Reading");
    String input = mySerial.readString();
    Serial.println(input);
  }
  delay(20);
}

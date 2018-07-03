#include <AccelStepper.h>
#include <limits.h>

#define STEPSIZE 1600

const int a_steer_pin = A0;
const int a_throttle_pin = A1;
const int a_brake_pin = A2;

int PUL=7;
int DIR=6;
int ENA=5;

signed char s_val;
signed char t_val;
signed char b_val;

float changeRange(int val, int low, int high, int newLow, int newHigh){
    return (float)(val - low) * (newHigh - newLow) / (float)(high - low) + newLow;
}

/* 2 = TX, 3 = RX */
SoftwareSerial wireless(2, 3);

void setup()
{  
   /* wireless 9600 baudrate */
   wireless.begin(9600); 
   
}

void loop()
{  
   signed char buf[3];
   s_val = analogRead(a_steer_pin);
   s_val = map(s_val, 0, 1023, SCHAR_MIN, SCHAR_MAX);
   t_val = analogRead(a_throttle_pin);
   t_val = map(t_val, 0, 1023, SCHAR_MIN, SCHAR_MAX);
   b_val = analogRead(a_steer_pin);
   b_val = map(b_val, 0, 1023, SCHAR_MIN, SCHAR_MAX);

   buf = {s_val, t_val, b_val};

   wireless.write(buf, 3);
   delay(5);
}

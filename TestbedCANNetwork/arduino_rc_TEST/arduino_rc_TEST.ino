#include <AccelStepper.h>
#include <limits.h>

#define STEPSIZE 1600

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
   s_val = 500; 
   s_val = map(s_val, 0, 1023, SCHAR_MIN, SCHAR_MAX);
   t_val = 600;
   t_val = map(t_val, 0, 1023, SCHAR_MIN, SCHAR_MAX);
   b_val = 250;
   b_val = map(b_val, 0, 1023, SCHAR_MIN, SCHAR_MAX);

   buf = {s_val, t_val, b_val};

   wireless.write(buf, 3);
   delay(5);
}

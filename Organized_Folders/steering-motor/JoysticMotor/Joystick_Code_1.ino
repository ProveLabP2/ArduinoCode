//HC-12 messenger send/receive
//autor Tom Heylen tomtomheylen.com

#include <SoftwareSerial.h>
#include <mcp2515.h>
#include <mcp2515_defs.h>
#include <Canbus.h>
//#include "TB_CAN_BUS.h"

const int X_pin = 0; // analog pin connected to X output
const int Y_pin = 1; // analog pin connected to Y output

void setup() {
  Serial.begin(9600);
  if (Canbus.init(CANSPEED_500)) {
    Serial.println("CAN Init ok");
  } else {
    Serial.println("CAN NOT INITIALIZED");
  }

  delay(1000);

}

void loop() {
  int s_val = analogRead(X_pin);                //Steering message
  unsigned char s_transl = map(s_val, 0, 1023, 0, 255);
  
  int t_val = analogRead(Y_pin);                //Throttle message
  unsigned char t_transl = map(t_val, 0 ,1023, 0, 255);
  
  //unsigned char b_val = wireless.read()                    //Brake message currently disables due to lack of input

  if(t_transl < 290 || t_transl > 230)
    {


        tCAN steer_message;
        steer_message.id = 0x10;
        steer_message.header.rtr = 0;
        steer_message.header.length = 1;
        steer_message.data[0] = s_transl;
        mcp2515_bit_modify(CANCTRL, (1 << REQOP2) | (1 << REQOP1) | (1 << REQOP0), 0);
        mcp2515_send_message(&steer_message);
        delay(100);
        Serial.print(" Data Steering: ");
        Serial.println(int(s_transl));
    }
  if(s_transl < 290 || s_transl > 230)
  {
          tCAN throttle_message;
          throttle_message.id = 0x20;
          throttle_message.header.rtr = 0;
          throttle_message.header.length = 1;
          throttle_message.data[0] = t_val;
          mcp2515_bit_modify(CANCTRL, (1 << REQOP2) | (1 << REQOP1) | (1 << REQOP0), 0);
          mcp2515_send_message(&throttle_message);
          delay(100);
          Serial.print(" Data Throttle: ");
          Serial.println(int(t_transl));
  }
  
  /*        tCAN brakes_message;
          brakes_message.id = B_ID;
          brakes_message.rtr = 0;
          brakes_message.length = 1;
          brakes_message.data[0] = b_val;
          mcp2515_bit_modify(CANCTRL, (1<<REQOP2)|(1<<REQOP1)|(1<<REQOP0), 0);
          mcp2515_send_message(&brakes_message);*/
}

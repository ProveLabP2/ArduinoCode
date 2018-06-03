//HC-12 messenger send/receive
//autor Tom Heylen tomtomheylen.com

#include <SoftwareSerial.h>
#include <mcp2515.h>
#include <mcp2515_defs.h>
#include <Canbus.h>
#include "TB_CAN_BUS.h"

SoftwareSerial wireless(2, 3); //RX, TX

void setup() {
    wireless.begin(9600);
    Serial.begin(9600);
    if(canbus.init(CANSPEED_500)){
        Serial.println("CAN Init ok");
    } else {
        Serial.println("CAN NOT INITIALIZED");
    }

    delay(1000);
}

void loop() {
    if(wireless.available() >= 3){//Read from HC-12 and send to serial monitor
        signed char s_val = wireless.read()
        signed char t_val = wireless.read()
        signed char b_val = wireless.read()

        tCAN steer_message;
        steer_message.id = S_ID;
        steer_message.rtr = 0;
        steer_message.length = 1;
        steer_message.data[0] = s_val;
        mcp2515_bit_modify(CANCTRL, (1<<REQOP2)|(1<<REQOP1)|(1<<REQOP0), 0);
        mcp2515_send_message(&steer_message);

        tCAN throttle_message;
        throttle_message.id = T_ID;
        throttle_message.rtr = 0;
        throttle_message.length = 1;
        throttle_message.data[0] = t_val;
        mcp2515_bit_modify(CANCTRL, (1<<REQOP2)|(1<<REQOP1)|(1<<REQOP0), 0);
        mcp2515_send_message(&throttle_message);

        tCAN brakes_message;
        brakes_message.id = B_ID;
        brakes_message.rtr = 0;
        brakes_message.length = 1;
        brakes_message.data[0] = b_val;
        mcp2515_bit_modify(CANCTRL, (1<<REQOP2)|(1<<REQOP1)|(1<<REQOP0), 0);
        mcp2515_send_message(&brakes_message);
    }
}

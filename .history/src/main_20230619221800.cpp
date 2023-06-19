#include <Arduino.h>
#include <IBusBM.h>
#include <iostream>

IBusBM IBus;    // IBus object
int vals[6];    // array to hold channel values

void setup() {
    // put your setup code here, to run once:

    Serial.begin(115200);     // debug info
    Serial2.begin(115200);    // iBUS input from receiver
    Serial2.setPins(12,13);   // set RX1 to pin 12 and TX1 to pin 13
    
    IBus.begin(Serial2,1);    // iBUS object connected to serial2 RX2 pin and use timer 1
}

void loop() {
    // put your main code here, to run repeatedly:

    // read channel 1-6
    for (int i=0; i<6; i++) {
        vals[i] = IBus.readChannel(i);
        // print channel values
        Serial.print("Channel ");
        Serial.print(i+1);
        Serial.print(": ");
        Serial.print(vals[i]);
        Serial.print("\t");
    }
    Serial.println("\n");
    
    
    delay(100);
}
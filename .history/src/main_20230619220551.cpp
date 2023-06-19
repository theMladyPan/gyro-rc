#include <Arduino.h>
#include <IBusBM.h>


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
        val = IBus.readChannel(i); // get latest value for servo channel 1
        Serial.print("Channel ");
        Serial.print(i);
        Serial.print(": ");
        Serial.println(val);
    }
    
    val = IBus.readChannel(0); // get latest value for servo channel 1
    Serial.print("Channel 1: ");
    Serial.println(val);
    delay(100);
}
#include <Arduino.h>
#include <IBusBM.h>


IBusBM IBus;    // IBus object
int val;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);     // debug info
  Serial1.begin(115200);    // iBUS input from receiver
  Serial1.setPins(12,13);   // set RX1 to pin 12 and TX1 to pin 13
  
  IBus.begin(Serial1,1);    // iBUS object connected to serial2 RX2 pin and use timer 1
}

void loop() {
  // put your main code here, to run repeatedly:

  val = IBus.readChannel(0); // get latest value for servo channel 1
  Serial.print("Channel 1: ");
  Serial.println(val);
  delay(100);
}
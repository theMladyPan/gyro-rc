#include <Arduino.h>
#include <IBusBM.h>


IBusBM IBus;    // IBus object
int val;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);     // debug info

  IBus.begin(Serial2,1);    // iBUS object connected to serial2 RX2 pin and use timer 1
}

void loop() {
  // put your main code here, to run repeatedly:

  val = IBus.readChannel(0); // get latest value for servo channel 1
  Serial.print("Channel 1: ");
  Serial.println(val);
}
/*
  IR Print Remote Signal

  Uses the sensor to get infrared signals emited by remote control
  and print them to the serial monitor
  
  The circuit:
  - CHQ1838D 
    VCC pin of the sensor to the +5V
    GND pin to the ground
    D0 pin to digital input 4 
  
  Created 2 Dec 2025
  By Sebastian Duque
*/

#include <IRremote.hpp> //version 4.5.0

const int digitalDataPin = 4;

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(digitalDataPin, ENABLE_LED_FEEDBACK);
}

void loop() {
  if (IrReceiver.decode()) {  // Grab an IR code
    IrReceiver.printIRResultShort(&Serial);
    Serial.print("Command: ");
    Serial.println(IrReceiver.decodedIRData.command, HEX);
    Serial.print("Address: ");
    Serial.println(IrReceiver.decodedIRData.address, HEX);
    delay(80);
    IrReceiver.resume();
  }
}

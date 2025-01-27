/*
  Light Sensor

  Reads the LDR Photoresistor Light Detection Sensor Module,
  makes a convertion of the digital output to bright and dark,
  and then prints the convertion accordingly.

  The circuit:
  - LDR module (this module version only has 3 pins, other versions
    have a 4th pin for analog output)
    VCC pin of the module to the +5V
    The middle pin to ground
    The DO pin to digital input 2

  Note: The sensor module has a potentiometer to adjust 
  the sensitivity, turning it all the way counter
  clockwise would be 0°, and rotating it clockwise would be 270° (max range)
  * 0°: will need a huge amount of light to mark bright, more than 2000 lumens,
    flashlight pointed directly still mark dark
  * 90°: will need a high amount of light to mark bright, about 1800 lumens,
    flashlight pointed directly marks bright
  * 180°: will need a moderate amount of light to mark bright, about 1000 lumens
  * 270°: will need few light intensity to mark bright about 1 lumen
    (a candle)

  Created 26 Jan 2025
  By Sebastian Duque
*/

const int dataPin = 2;

int state = 0;
int lastState = 0;

void setup() {
  pinMode(dataPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  state = digitalRead(dataPin);
    // Only print the state of the sensor if there is a change in the state
  if (state != lastState) {
    lastState = state;
    printSensorState(state);
    delay(1000);
  }
}

void printSensorState(int state) {
  switch (state) {
    case 0:
      Serial.println("Bright");
      break;
    case 1:
      Serial.println("Dark");
      break;
    default:
      Serial.println("Undefined");
  }
}
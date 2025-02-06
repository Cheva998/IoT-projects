/*
  IR Distance

  Uses the sensor TCRT5000 to measure distance using infrared, the 
  digital indicates when there is an object being detected, and the 
  analog returns a numeric value for distance. When there is an object
  the program print the analog valu
  
  The circuit:
  - TCRT5000 
    VCC pin of the sensor to the +5V
    GND pin to the ground
    D0 pin to digital input 3
    A0 pin to analog input 

  Note: Unfortunately the sensor isn't very accurate, but it can be
  used to detect movement.
  The sensor has a potentiometer to adjust the sensitivity, 
  turning it all the way counter clockwise would be 0°, and rotating
  it clockwise would be 270° (max range)
  * 0°: Is the least sensitive, it don't detect any object
  * 10°: Needs to be very close (10 - 20 mm) to detect an object
  * 250°: It can detect objects at a 4 cm distance
  * 270°: Is the most sensitive, it alway detect an object, but the 
    analog will only give meaningful measures from 1 to 8 cm
  
  Created 26 Jan 2025
  By Sebastian Duque
*/

const int digitalDataPin = 3;
const int analogDataPin = A0;

bool digitalData;
int analogData;

void setup() {
  pinMode(digitalDataPin, INPUT);
  pinMode(analogDataPin, INPUT);
  pinMode(6, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  digitalData = digitalRead(digitalDataPin);
  analogData = analogRead(analogData);

  if (digitalData == 0) {
    Serial.print("Analog: ");
    Serial.println(analogData);
    delay(1000);
  }
}

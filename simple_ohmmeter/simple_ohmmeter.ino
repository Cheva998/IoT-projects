/*
  Simple Ohmmeter

  Calculates the electrical resistance of a resistor. This
  the circuit uses a known resistor of 500 ohm, the second 
  resistor "the unknown resistor" can be set any value, 
  and the calculated value with the program must be similar
  to the value of the resistance configured by the user
  
  The circuit:
   - Digital pin 4 to the beginning of known resistor
   - Analog pin A3 to the end of known resistor
   - A positive (red) cable goes from the end of the known 
     resistor to the beginning of the unknown resistor
   - A negative (black) cable goes from the end of the
     unknown resistor to ground (GND)

  A tinkercad version can be found in:
  https://www.tinkercad.com/things/lWJSlhPnqYF-simple-ohmmeter

  Created 12 Feb 2025
  By Sebastian Duque
*/

#define OHMMETER 4
#define READ_OHM A3
float knownResistor = 510.0; //ohms
float signal;
float voltage;
float resistance;

float measureOhm() {
  signal = analogRead(READ_OHM);
  voltage = signal * 5.0 / 1023.0;
  return voltage * knownResistor / (5.0 - voltage);
}

void setup() {
  pinMode(OHMMETER, OUTPUT);
  pinMode(READ_OHM, INPUT);
  digitalWrite(OHMMETER, HIGH);
  Serial.begin(9600);
}

void loop() {
  resistance = measureOhm();
  if (resistance > 0 && resistance < 100000) {
    Serial.print("Omhs: ");
    Serial.println(resistance, 2);
  }
  delay(1000);
}



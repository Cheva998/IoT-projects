/*
  Multimeter

  The program can be set to calculate voltage of a circuit or electrical
   resistance of a resistor.

  The circuit:
  

  
  Created 13 Feb 2025
  By Sebastian Duque
*/

#define VOLTAGE_OUT_PIN 4
#define READ_SIGNAL A3
int newMode = 0;
int mode = 0; // 1: voltage | 2: resistance
float knownResistor = 510.0; //ohms
float signal;
float voltage;
float resistance;

float measureOhm() {
  pinMode(VOLTAGE_OUT_PIN, OUTPUT);
  digitalWrite(VOLTAGE_OUT_PIN, HIGH);
  delay(5);
  signal = 0;
  for (int i = 0; i < 5; i++) {
    signal += analogRead(READ_SIGNAL);
    delay(5);
  }
  signal /= 5;
  voltage = signal * 5.0 / 1023.0;
  // pinMode(VOLTAGE_OUT_PIN, INPUT);
  digitalWrite(VOLTAGE_OUT_PIN, LOW);
  return voltage * knownResistor / (5.0 - voltage);
}

float measureVoltage() {
  signal = 0;
  for (int i = 0; i < 5; i++) {
    signal += analogRead(READ_SIGNAL);
    delay(5);
  }
  signal /= 5;
  return signal * 5.0 / 1023.0;
}

void setup() {
  pinMode(VOLTAGE_OUT_PIN, OUTPUT);
  pinMode(READ_SIGNAL, INPUT);
  digitalWrite(VOLTAGE_OUT_PIN, LOW);
  Serial.begin(9600);
}

void loop() {
  newMode = Serial.parseInt();
  if (newMode > 0) {
    mode = newMode;
    Serial.print("mode: ");
    Serial.println(mode);
  }
  switch (mode) {
    case 1:
      voltage = measureVoltage();
      Serial.print(voltage);
      Serial.println(" V");
      break;
    case 2:
      resistance = measureOhm();
      Serial.print(resistance);
      Serial.println(" Ohm");
      break;
    default:
      Serial.println("Invalid mode entered");
  }
  delay(1000);
}

























/*
  Serial Send Integer

  Reads an integer value between 1 and 9 using the usb serial,
  then writes that same number to the serial, and blinks the builtin
  led that number of times.
  This a test to connect a Raspberry to an Arduino, and check if the
  connection works
  
  The circuit:
  - Arduino Uno
  - Raspberry pi
  
  Created 12 Oct 2025
  By Sebastian Duque
*/

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}

void blink(int n) {
  for (int i = 0; i < n; i++) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(200);
    digitalWrite(LED_BUILTIN, LOW);
    delay(200);
  }
}

void loop() {
  int n = Serial.parseInt();
  if (n > 0 && n < 10) {
    Serial.print(n);
    blink(n);
  }
}

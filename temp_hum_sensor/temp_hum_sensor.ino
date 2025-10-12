/*
  Temperatuere Humidity Sensor

  Uses the sensor DHT11 to measure temperature and humidity 
  and prints it into the serial monitor
  
  The circuit:
  - DHT11 
    + pin of the sensor to the +5V
    - pin to the ground
    out pin to digital input 3
  
  Created 26 Jan 2025
  By Sebastian Duque
*/


#include "DHT.h"

int data_pin = 2;
int print_interval = 10000;

#define DHTTYPE DHT11

DHT dht(data_pin, DHTTYPE);

void setup() {
  pinMode(data_pin, INPUT);
  Serial.begin(9600);
  delay(50);
  dht.begin();
}

void loop() {
  float hum = dht.readHumidity();
  float temp = dht.readTemperature();
  if (isnan(hum) || isnan(temp)) {
    Serial.println("Failed to read the data");
  }
  float hic = dht.computeHeatIndex(false);
  printSensorData(temp, hum, hic);
  delay(print_interval);
}

void printSensorData(float temp, float hum, float hic) {
  Serial.println("Temp\tHum\tHI°C");
  Serial.print(temp, 1);
  Serial.print("°C\t");
  Serial.print(hum, 1);
  Serial.print("%\t");
  Serial.print(hic, 1);
  Serial.print("°C");
  Serial.println();
}
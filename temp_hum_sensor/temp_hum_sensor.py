"""
  Temperature Humidity Sensor

  Uses the sensor DHT11 to measure temperature and humidity
  and print the selected variable
  
  The circuit:
  - DHT11 
    + pin of the sensor to the +5V (pin 4) raspberry
    - pin to the ground (pin 6) raspberry
    out pin (marked with "s") to D4 (pin 7) raspberry
  
  Created 4 Jan 2026
  By Sebastian Duque
"""

import board
import adafruit_dht

pin = board.D4
dht = adafruit_dht.DHT11(pin, use_pulseio=False)

def get_temperature():
    try:    
        return dht.temperature
    except Exception as e:
        print(f'Error with temperature reading: {e}')

def get_humidity():
    try:
        return dht.humidity
    except Exception as e:
        print(f'Error with humidity reading: {e}')

def main():
    while True:
        sensor = input('Enter the sensor type -> t for temp, h for humidity and q for quit: ')
        if sensor == 't':
            print(get_temperature())
            continue
        if sensor == 'h':
            print(get_humidity())
            continue
        if sensor == 'q':
            break

if __name__ == "__main__":
    main()

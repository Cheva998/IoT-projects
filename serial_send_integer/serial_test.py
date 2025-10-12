"""
  Serial Test

  Reads an integer value between 1 and 9 using the prompt,
  then writes that same number to the serial connected to an Arduino, 
  and reads back the same number as response from the Arduino.
  This a test to connect a Raspberry to an Arduino, and check if the
  connection works
  
  The circuit:
  - Arduino Uno
  - Raspberry pi
  
  Created 12 Oct 2025
  By Sebastian Duque
"""

import serial

serial_port = '/dev/ttyACM0'
baud_rate = 9600
ENCODING = 'utf-8'
BYTE_SIZE = 1

with serial.Serial(serial_port, baud_rate, timeout = 5) as ser:
    while 1:
        n = input('Enter number between 1 - 9 (0 for exit): ')
        try:
            number = int(n)
        except ValueError:
            continue
        if n == '0':
            break
        if number >= 0 and number <= 9:
            data = ser.write(n.encode(ENCODING))
            response_data = ser.read(BYTE_SIZE).decode(ENCODING)
            ser.flush()
            print(f'Number: {response_data}. Data type: {type(response_data)}')
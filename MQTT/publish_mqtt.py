"""
  Publish Temperature with MQTT

  Uses the sensor DHT11 to measure temperature
  and send the data to Adafruit IO with MQTT protocol
  
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
import paho.mqtt.client as mqtt
from dotenv import load_dotenv
import os
import time

load_dotenv()

ADAFRUIT_USER = os.environ.get("ADAFRUIT_USER")
ADAFRUIT_KEY = os.environ.get("ADAFRUIT_KEY")
ADAFRUIT_FEED = 'temperature-humidity'

MQTT_BROKER = 'io.adafruit.com'
MQTT_PORT = 1883
MQTT_TOPIC = f"{ADAFRUIT_USER}/feeds/{ADAFRUIT_FEED}"

pin = board.D4
dht = adafruit_dht.DHT11(pin, use_pulseio=False)

def get_temperature():
    try:    
        return dht.temperature
    except Exception as e:
        print(f'[X] Error with temperature reading: {e}')
        
def on_connect(client, userdata, flags, reason_code, properties):
    if reason_code.is_failure:
        print(f"Failed to connect: {reason_code}. loop_forever() will retry connection")
    else:
        print('Connection successful')

def main():
    client = mqtt.Client(mqtt.CallbackAPIVersion.VERSION2)
    client.on_connect = on_connect
    client.username_pw_set(ADAFRUIT_USER, ADAFRUIT_KEY)
    
    client.connect(MQTT_BROKER, MQTT_PORT, 60)
    client.loop_start()
    print(f"[>] Publishing data to Adafruit IO topic: {MQTT_TOPIC}")
    time.sleep(2)
    temp = get_temperature()
    client.publish(MQTT_TOPIC, temp)
    print(f"[>] Sent: {temp}")
    client.disconnect()
    client.loop_stop()
    
if __name__ == "__main__":
    main()
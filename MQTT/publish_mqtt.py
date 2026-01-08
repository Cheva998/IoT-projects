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
ADAFRUIT_TEMP_FEED = 'home-sensors.temperature'
ADAFRUIT_HUM_FEED = 'home-sensors.humidity'
TIME_INTERVAL = 60

MQTT_BROKER = 'io.adafruit.com'
MQTT_PORT = 1883
MQTT_TEMP_TOPIC = f"{ADAFRUIT_USER}/feeds/{ADAFRUIT_TEMP_FEED}"
MQTT_HUM_TOPIC = f"{ADAFRUIT_USER}/feeds/{ADAFRUIT_HUM_FEED}"

READ_SENSOR_ATTEMPTS = 3
pin = board.D4
dht = adafruit_dht.DHT11(pin, use_pulseio=False)

def get_temperature():
    try:
        return dht.temperature
    except Exception as e:
        print(f'[X] Error with temperature reading: {e}')

def get_humidity():
    try:
        return dht.humidity
    except Exception as e:
        print(f'[X] Error with humidity reading: {e}')

def on_connect(client, userdata, flags, reason_code, properties):
    if reason_code.is_failure:
        print(f"Failed to connect: {reason_code}. loop_forever() will retry connection")
    else:
        print('Connection successful')

def on_publish(client, userdata, mid, reason_code, properties):
    print('Publish confirmed')
    #print(f'mid: {mid}\nuserdata: {userdata}')

def read_sensor(var_to_read):
    wait_time = 1
    for _ in range(READ_SENSOR_ATTEMPTS):
        var = var_to_read()
        if var:
            return var
        else:
            print(f'Variable read failed waiting {wait_time}s')
            time.sleep(wait_time)
            wait_time *= 2
    return 0

def main():
    last_sent = 0
    client = mqtt.Client(mqtt.CallbackAPIVersion.VERSION2)
    client.on_connect = on_connect
    client.on_publish = on_publish
    client.username_pw_set(ADAFRUIT_USER, ADAFRUIT_KEY)
    
    client.connect(MQTT_BROKER, MQTT_PORT, 60)
    client.loop_start()
    print(f"[>] Publishing data to Adafruit IO topic: {MQTT_TEMP_TOPIC}")
    sent = 0
    while True:
        time_sent = time.time()
        if time_sent - last_sent >= TIME_INTERVAL:
            temp = read_sensor(get_temperature)
            client.publish(MQTT_TEMP_TOPIC, temp, qos=2)
            hum = read_sensor(get_humidity)
            client.publish(MQTT_HUM_TOPIC, hum, qos=2)
            last_sent = time_sent
            sent += 1
            print(f"[>] Sent: {temp}°C - {hum}%")

    client.disconnect()
    client.loop_stop()
    
if __name__ == "__main__":
    main()
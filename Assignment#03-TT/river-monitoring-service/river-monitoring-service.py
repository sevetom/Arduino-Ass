import paho.mqtt.client as mqtt
from flask import Flask, jsonify, request
import serial
import time
import json
import os

# Function to load MQTT configuration from file
def load_mqtt_config():
    # controllo se il file di configurazione esiste
    if not os.path.exists("../config/mqttConfig.json"):
        default_config = {
        "mqtt_server": "mqtt.example.com",
        "mqtt_port": 1883,
        "mqtt_topic": "topic/default",
        "mqtt_username": "user",
        "mqtt_password": "password"
        }
        with open("../config/mqttConfig.json", "w") as config_file:
            json.dump(default_config, config_file)
        
    # leggo il file di configurazione
    with open("../config/mqttConfig.json", "r") as config_file:
        config_data = json.load(config_file)
        return (
            config_data["mqtt_server"],
            config_data["mqtt_port"],
            config_data["mqtt_topic"],
            config_data["mqtt_username"],
            config_data["mqtt_password"]
        )
        
# Function to load Arduino configuration from file
def load_arduino_config():
    with open("../config/arduinoConfig.json", "r") as config_file:
        config_data = json.load(config_file)
        return (
            config_data["serial_port"],
            config_data["baud_rate"]
        )

# Connects to the mqtt server
mqtt_server, mqtt_port, mqtt_topic, mqtt_username, mqtt_password = load_mqtt_config()
mqtt_client = mqtt.Client()
mqtt_client.username_pw_set(username=mqtt_username, password=mqtt_password)
mqtt_client.connect(mqtt_server, mqtt_port, 60)
mqtt_client.subscribe(mqtt_topic)

# Connects to the arduino
arduino_serial_port, arduino_serial_baudrate = load_arduino_config()

# Sets up the flask app
app = Flask(__name__)

# Water Level Thresholds
WL1 = 10
WL2 = 20
WL3 = 30
WL4 = 40

# Monitoring Frequencies in seconds
F1 = 60
F2 = 30

# Valve Opening Levels
valve_normal = 25
valve_alarm_low = 0
valve_pre_alarm_high = 25
valve_alarm_high = 50
valve_critic_high = 100

# States of the system
normal_state = "NORMAL"
alarm_too_low = "ALARM-TOO-LOW"
pre_alarm_too_high = "PRE-ALARM-TOO-HIGH"
alarm_too_high = "ALARM-TOO-HIGH"
alarm_too_high_critic = "ALARM-TOO-HIGH-CRITIC"

# Initial state
current_state = "NORMAL"
# Initial monitoring frequency
monitoring_frequency = F1
# Initial valve opening level
valve_opening_level = valve_normal
# Water Level
water_level = 0

# Sends the data to the arduino and the mqtt client
def send_data():
    global monitoring_frequency
    global valve_opening_level

    with serial.Serial(arduino_serial_port, arduino_serial_baudrate) as ser:
        ser.write(f"{valve_opening_level}\n".encode())

    mqtt_payload = json.dumps({"frequency": monitoring_frequency})
    mqtt_client.publish(mqtt_topic, mqtt_payload)

# Changes the values dependening on the state
def change_state(state, frequency, opening_level):
    global current_state
    global monitoring_frequency
    global valve_opening_level
    
    current_state = state
    monitoring_frequency = frequency
    valve_opening_level = opening_level

# Callback for when a message is received from the mqtt client
def on_message(client, userdata, msg):
    global current_state
    global monitoring_frequency
    global valve_opening_level
    global water_level

    water_level = int(msg.payload.decode())

    if WL1 <= water_level <= WL2:
        change_state(normal_state, F1, valve_normal)
    elif water_level < WL1:
        change_state(alarm_too_low, F1, valve_alarm_low)
    elif WL2 < water_level <= WL3:
        change_state(pre_alarm_too_high, F2, valve_pre_alarm_high)
    elif WL3 < water_level <= WL4:
        change_state(alarm_too_high, F2, valve_alarm_high)
    else:
        change_state(alarm_too_high_critic, F2, valve_critic_high)
        
    send_data()

# Returns the status of the system via an HTTP request
@app.route("/status", methods=["GET"])
def get_status():
    global water_level, current_state, valve_opening_level
    return jsonify({
        "water_level": water_level,
        "system_state": current_state,
        "valve_opening_level": valve_opening_level
    })

# Changes the valve opening level via an HTTP request
@app.route("/control", methods=["POST"])
def control_valve():
    global current_state, monitoring_frequency, valve_opening_level
    try:
        # Ottieni il livello di apertura desiderato dalla richiesta
        valve_level = int(request.form.get("valve_level"))
        change_state(current_state, monitoring_frequency, valve_level)
        return jsonify({"success": True})
    except Exception as e:
        return jsonify({"success": False, "message": str(e)}), 500

if __name__ == "__main__":
    mqtt_client.on_message = on_message
    mqtt_client.loop_start()
    app.run(port=5001)
    send_data()

    try:
        while True:
            time.sleep(1)
    except KeyboardInterrupt:
        mqtt_client.disconnect()
        mqtt_client.loop_stop()
import paho.mqtt.client as mqtt
from flask import Flask, jsonify, request
from flask_cors import CORS
import serial
import time
import threading

'''
@author tommaso.ceredi@studio.unibo.it
@author tommaso.severi2@studio.unibo.it
'''

# Connects to the mqtt server
mqtt_server = "192.168.178.31"
mqtt_port = 1883
mqtt_topic_read = "water-level"
mqtt_topic_send = "monitoring-frequency"
mqtt_client = mqtt.Client()
mqtt_client.connect(mqtt_server, mqtt_port, 60)
mqtt_client.subscribe(mqtt_topic_read)

# Arduino config
arduino_serial_port = "COM3"
arduino_serial_baudrate = "9600"
ser = serial.Serial(arduino_serial_port, arduino_serial_baudrate)

# Sets up the flask app
app = Flask(__name__)
CORS(app)

# Water Level Thresholds
WL1 = 10
WL2 = 20
WL3 = 30
WL4 = 40

# Monitoring Frequencies in seconds
F1 = 2000
F2 = 4000

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
automatic_modality = "automatic"
manual_modality = "manual"
modality_change = 101

# Initial state
current_mode = normal_state
system_modality = automatic_modality
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

    ser.write(f"{valve_opening_level}\n".encode())
    print(f"Sending arduino: {valve_opening_level}")

    mqtt_payload = f"{monitoring_frequency}"
    print(f"Sending: {mqtt_payload}")
    mqtt_client.publish(mqtt_topic_send, mqtt_payload)

def read_serial():
    global system_modality
    while True:
        if ser.in_waiting:
            packet = ser.readline().decode("utf").rstrip("\n")
            print(packet)
            if not packet or not packet.startswith("Modality: ") or packet == system_modality:
                continue
            mod = float(packet.split(" ")[2])
            system_modality = automatic_modality if mod == 0 else manual_modality;
            print("changed: " + system_modality)

# Changes the values dependening on the state
def change_state(state, frequency, opening_level):
    global current_state
    global monitoring_frequency
    global valve_opening_level
    
    current_state = state
    monitoring_frequency = frequency
    valve_opening_level = opening_level
    send_data()
    
def change_modality(modality):
    global system_modality
    system_modality = modality
    ser.write(f"{modality_change}\n".encode())

# Callback for when a message is received from the mqtt client
def on_message(client, userdata, msg):
    if (msg.topic != mqtt_topic_read or system_modality == manual_modality):
        return

    global current_state
    global monitoring_frequency
    global valve_opening_level
    global water_level

    water_level = str(msg.payload.decode("utf-8"))
    water_level = int(water_level)
    print(f"Water Level int: {water_level}")

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

# Returns the status of the system via an HTTP request
@app.route("/status", methods=["GET"])
def get_status():
    global water_level, current_state, valve_opening_level, system_modality
    return jsonify({
        "water_level": water_level,
        "system_state": current_state,
        "valve_opening_level": valve_opening_level,
        "system_modality": system_modality
    })

# Changes the valve opening level via an HTTP request
@app.route("/control", methods=["POST"])
def control_valve():
    global current_state, monitoring_frequency, valve_opening_level, system_modality
    try:
        if (system_modality == automatic_modality):
            change_modality()
        valve_level = int(request.form.get("valve_level"))
        change_state(current_state, monitoring_frequency, valve_level)
        return jsonify({"success": True})
    except Exception as e:
        return jsonify({"success": False, "message": str(e)}), 500

if __name__ == "__main__":
    mqtt_client.on_message = on_message
    mqtt_client.loop_start()
    print("MQTT Client started")
    t1 = threading.Thread(target=app.run, kwargs={'port': 5001, 'debug': False})
    t1.start()
    try:
        while True:
            read_serial()
            time.sleep(1)
    except KeyboardInterrupt:
        mqtt_client.disconnect()
        mqtt_client.loop_stop()
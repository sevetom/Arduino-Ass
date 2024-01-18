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
WL1 = 50
WL2 = 80
WL3 = 100
WL4 = 140

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
# modalities of the system
automatic_modality = "automatic"
manual_modality = "manual"
# modalities used to transition from automatic to manual and viceversa
# this are plus one for serial line problems
manual_change = 101+1
automatic_change = 102+1

# Initial state
current_mode = normal_state
system_modality = automatic_modality
# Initial monitoring frequency
monitoring_frequency = F1
# Initial valve opening level
valve_opening_level = valve_normal
# Water Level
water_level = 0

current_state = "initial_state"
monitoring_frequency = 0

# Sends the data to the arduino and the mqtt client
def send_data():
    global monitoring_frequency
    global valve_opening_level
    # every value sent to arduino is plus 1 since
    # 0 was creating issues on the serial line
    tmp = valve_opening_level+1
    ser.write(f"{tmp}\n".encode())
    print(f"PY Sending arduino: {tmp}")

    mqtt_payload = f"{monitoring_frequency}"
    print(f"PY Sending: {mqtt_payload}")
    mqtt_client.publish(mqtt_topic_send, mqtt_payload)

def read_serial():
    global system_modality
    while True:
        if ser.in_waiting:
            packet = ser.readline().decode("utf").rstrip("\n")
            print(packet)
            if not packet or not packet.startswith("Modality: ") or packet == system_modality:
                continue
            mod = float(packet.split(" ")[1])
            system_modality = automatic_modality if mod == automatic_change-1 else manual_modality
            print("PY changed: " + system_modality)

# Changes the values dependening on the state
def change_state(state, frequency, opening_level):
    global current_state
    global monitoring_frequency
    global valve_opening_level
    
    current_state = state
    monitoring_frequency = frequency
    valve_opening_level = opening_level
    send_data()

# Changes the modality of the system and notifies arduino
def change_modality(modality):
    global system_modality
    system_modality = modality
    if (modality == manual_modality):
        ser.write(f"{manual_change}\n".encode())
    else:
        ser.write(f"{automatic_change}\n".encode())

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
    print(f"PY Water Level int: {water_level}")

    # calculate the new state
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
    # notify all the other systems 
    send_data()

# Returns the status of the system via an HTTP request
@app.route("/status", methods=["GET"])
def get_status():
    global water_level, current_state, valve_opening_level, system_modality
    print(f"PY STATUS current modal: {system_modality} and current state: {current_state}")
    return jsonify({
        "water_level": water_level,
        "system_state": current_state,
        "valve_opening_level": valve_opening_level,
        "system_modality": system_modality
    })

# Changes the valve opening level via an HTTP request
@app.route("/control", methods=["POST"])
def control_valve():
    global current_state, monitoring_frequency, system_modality
    try:
        valve_level = int(request.form.get("valve_level"))
        print(f"PY CONTROL Valve level: {valve_level}")
        if (valve_level < 0 and system_modality == manual_modality):
            print("PY CONTROL Changing modality to automatic")
            change_modality(automatic_modality)
        else:
            if (system_modality == automatic_modality):
                print("PY CONTROL Changing modality to manual")
                change_modality(manual_modality)
            change_state(current_state, monitoring_frequency, valve_level)
        return jsonify({"success": True})
    except Exception as e:
        print("PY CONTROL Error: " + str(e))
        return jsonify({"success": False, "message": str(e)}), 500

if __name__ == "__main__":
    mqtt_client.on_message = on_message
    mqtt_client.loop_start()
    print("PY MQTT Client started")
    t1 = threading.Thread(target=app.run, kwargs={'port': 5001, 'debug': False})
    t1.start()
    try:
        while True:
            read_serial()
    except KeyboardInterrupt:
        mqtt_client.disconnect()
        mqtt_client.loop_stop()
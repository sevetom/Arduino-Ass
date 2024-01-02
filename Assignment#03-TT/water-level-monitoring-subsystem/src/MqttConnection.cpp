#include "mqttConnection.h"

MqttConnection::MqttConnection(const char* wifi_ssid, const char* wifi_password, const char* mqtt_server, 
        int mqtt_port, const char* mqtt_topic): espClient(), client(espClient) {
    this->wifi_ssid = wifi_ssid;
    this->wifi_password = wifi_password;
    this->mqtt_server = mqtt_server;
    this->mqtt_port = mqtt_port;
    this->mqtt_topic = mqtt_topic;
}

void MqttConnection::connect() {
    WiFi.begin(this->wifi_ssid, this->wifi_password);
    Serial.println("Connecting to WiFi");
    while(WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("");
    Serial.print("Connected to WiFi network with IP Address: ");
    Serial.println(WiFi.localIP());
    client.setServer(this->mqtt_server, this->mqtt_port);
    client.setCallback([this](char* topic, byte* payload, unsigned int length) { 
        staticCallback(topic, payload, length, this);
    });
}

void MqttConnection::reconnectServer() {
    while (!this->client.connected()) {
        Serial.println("Attempting MQTT connection...");
        if (this->client.connect("ESP32Client")) {
            Serial.println("Connected to MQTT");
            this->client.subscribe(this->mqtt_topic);
        } else {
            Serial.print("Failed, rc=");
            Serial.print(this->client.state());
            Serial.println(" Retrying in 5 seconds");
            delay(5000);
        }
  }
}

void MqttConnection::sendMessagge(char* message) {
    this->client.publish(this->mqtt_topic, message);
}

bool MqttConnection::getStatus() {
    return this->client.connected();
}

byte* MqttConnection::getMessageReceived() {
    return this->messageReceived;
}

void MqttConnection::tick() {
    this->client.loop();
}

void MqttConnection::callback(char* topic, byte* payload, unsigned int length) {
    if (topic == this->mqtt_topic) {
        this->messageReceived = payload;
    }
}

void MqttConnection::staticCallback(char* topic, byte* payload, unsigned int length, MqttConnection* instance) {
    instance->callback(topic, payload, length);
}
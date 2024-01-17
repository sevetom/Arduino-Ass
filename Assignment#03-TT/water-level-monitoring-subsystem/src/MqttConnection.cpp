#include "mqttConnection.h"

MqttConnection::MqttConnection(const char* wifi_ssid, const char* wifi_password, const char* mqtt_server, 
        int mqtt_port, const char* mqtt_topic_read, const char* mqtt_topic_send): espClient(), client(espClient) {
    this->wifi_ssid = wifi_ssid;
    this->wifi_password = wifi_password;
    this->mqtt_server = mqtt_server;
    this->mqtt_port = mqtt_port;
    this->mqtt_topic_read = mqtt_topic_read;
    this->mqtt_topic_send = mqtt_topic_send;
}

void MqttConnection::connect() {
    WiFi.begin(this->wifi_ssid, this->wifi_password);
    delay(100);
    while(WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("");
    Serial.print("Connected to WiFi network with IP Address: ");
    Serial.println(WiFi.localIP());
    this->client.setServer(this->mqtt_server, this->mqtt_port);
}

void MqttConnection::setCall(std::function<void (char *, uint8_t *, unsigned int)> callback) {
    this->client.setCallback(callback);
}

void MqttConnection::reconnectServer() {
    while (!this->client.connected()) {
        Serial.println("Attempting MQTT connection...");
        if (this->client.connect("ESP32Client")) {
            Serial.println("Connected to MQTT");
            this->client.subscribe(this->mqtt_topic_read);
        } else {
            Serial.print("Failed, rc=");
            Serial.print(this->client.state());
            Serial.println(" Retrying in 5 seconds");
            delay(5000);
        }
  }
}

void MqttConnection::sendMessagge(char* message) {
    Serial.println("Sending message" + String(message));
    this->client.publish(this->mqtt_topic_send, message);
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

char* MqttConnection::getTopic() {
    return (char*)this->mqtt_topic_read;
}
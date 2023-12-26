#include "mqttConnection.h"

MqttConnection::MqttConnection(char* configFile) {
    this->configFile = configFile;
    if (!SPIFFS.begin(true)) {
        Serial.println("Failed to mount file system");
    }
}

void MqttConnection::connect() {
    WiFi.begin(ssid, password);
    Serial.println("Connecting to WiFi");
    while(WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("");
    Serial.print("Connected to WiFi network with IP Address: ");
    Serial.println(WiFi.localIP());
    client.setServer(this->getConfigValue("mqtt_server").c_str(), SEVER_PORT);
    client.setCallback(this->callback);
}

void MqttConnection::reconnectServer() {
    while (!this->client.connected()) {
        Serial.println("Attempting MQTT connection...");
        if (this->client.connect("ESP32Client", this->getConfigValue("mqtt_username"), this->getConfigValue("mqtt_password"))) {
            Serial.println("Connected to MQTT");
            this->client.subscribe(this->getConfigValue("mqtt_topic"));
        } else {
            Serial.print("Failed, rc=");
            Serial.print(this->client.state());
            Serial.println(" Retrying in 5 seconds");
            delay(5000);
        }
  }
}

void MqttConnection::sendMessagge(char* message) {
    this->client.publish(this->getConfigValue("mqtt_topic").c_str(), message);
}

bool MqttConnection::getStatus() {
    return this->client.connected();
}

void MqttConnection::tick() {
    this->client.loop();
}

String MqttConnection::this->getConfigValue(const char *key) {
  File configFile = SPIFFS.open(this->configFile, "r");
  size_t size = configFile.size();
  std::unique_ptr<char[]> buf(new char[size]);
  configFile.readBytes(buf.get(), size);
  configFile.close();
  DynamicJsonDocument jsonDoc(1024);
  deserializeJson(jsonDoc, buf.get());
  return jsonDoc[key].as<String>();
}

void callback(char *topic, byte *payload, unsigned int length) {
  // !TODO: Handle the message from the MQTT server
}
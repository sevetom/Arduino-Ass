#include "Components.h"
#include "MqttConnection.h"

#define MQTT_CONFIG "./mqttConfig.json"

void checkConnection();
void sendWaterLevel();
int getFrequency();

MqttConnection* connection;
Components* hw;

void setup() {
	Serial.begin(115200);
	hw = new Components();
	connection = new MqttConnection(MQTT_CONFIG);
	connection->connect();
}

void loop() {
	checkConnection();
	sendWaterLevel();
	delay(getFrequency());
}

void checkConnection() {
	if (!connection->getStatus()) {
		hw->greenLed->off();
		hw->redLed->on();
		connection->reconnectServer();
		hw->greenLed->on();
		hw->redLed->off();
	}
	connection->tick();
}

void sendWaterLevel() {
	char message[10];
	sprintf(message, "%d", hw->sonar->getDistance());
	connection->sendMessagge(message);
}

int getFrequency() {
	return atoi((char *)connection->getMessageReceived());
}

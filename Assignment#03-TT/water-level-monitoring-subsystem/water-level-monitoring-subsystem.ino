#include "Components.h"
#include "MqttConnection.h"

#define MQTT_CONFIG "./mqttConfig.json"

void checkConnection();
void readWaterLevel();

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
	readWaterLevel();
	// !TODO: Set the frequency of the water level reading
}

void readWaterLevel() {
	char message[10];
	sprintf(message, "%d", hw->sonar->getDistance());
	connection->sendMessagge(message);
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

#include "Components.h"
#include "MqttConnection.h"

#define MQTT_CONFIG "../config/mqttConfig.json"

/**
 * Checks the connection of the MQTT server 
 * and tries to reconnect if it is not connected.
*/
void checkConnection();
/**
 * Sends the water level to the MQTT server.
*/
void sendWaterLevel();
/**
 * Gets the frequency of the sonar from the MQTT server.
*/
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

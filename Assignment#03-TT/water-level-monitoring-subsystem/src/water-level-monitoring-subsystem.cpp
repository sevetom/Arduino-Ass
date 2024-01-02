#include "Components.h"
#include "MqttConnection.h"

/**
 * Checks the connection of the MQTT server 
 * and tries to reconnect if it is not connected.
*/
void checkConnection();
/**
 * Sends the water level to the MQTT server.p
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
	const char* wifi_ssid = "iCereLan-FASTWEB";
	const char* wifi_password = "iLanVeloce";
	const char* mqtt_server = "192.168.178.31";
	int mqtt_port = 1883;
	const char* mqtt_topic = "water-level";
	connection = new MqttConnection(wifi_ssid, wifi_password, mqtt_server, mqtt_port, mqtt_topic);
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

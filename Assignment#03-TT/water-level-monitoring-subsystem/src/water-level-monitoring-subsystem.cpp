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
int byteArrayToInt(const unsigned char* byteArray, size_t size);

void callback(char* topic, byte* payload, unsigned int length);

MqttConnection* connection;
Components* hw;
int frequency;

void setup() {
	Serial.begin(115200);
	hw = new Components();
	frequency = 0;
	const char* wifi_ssid = "iCereLan-FASTWEB";
	const char* wifi_password = "iLanVeloce";
	const char* mqtt_server = "192.168.178.31";
	int mqtt_port = 1883;
	const char* mqtt_topic_read = "monitoring-frequency";
	const char* mqtt_topic_send = "water-level";
	connection = new MqttConnection(wifi_ssid, wifi_password, mqtt_server, mqtt_port, mqtt_topic_read, mqtt_topic_send);
	connection->setCall(callback);
	connection->connect();
}

void loop() {
	checkConnection();
	sendWaterLevel();
	delay(frequency);
	delay(1000);
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

int byteArrayToInt(const unsigned char* byteArray, size_t size) {
    int result = 0;
    for (size_t i = 0; i < size; i++) {
        if (byteArray[i] >= '0' && byteArray[i] <= '9') {
            result = result * 10 + (byteArray[i] - '0');
        }
    }
    return result;
}

void callback(char* topic, byte* payload, unsigned int length) {
	if (topic == connection->getTopic()) {
		Serial.println();
		Serial.print("valore ricevuto: ");
		frequency = byteArrayToInt(payload, length);
		Serial.println(frequency);
	}
}

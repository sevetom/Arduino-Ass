#include "Components.h"
#include "MqttConnection.h"

#define CHANNEL_HEIGHT 150

/**
* @author tommaso.ceredi@studio.unibo.it
* @author tommaso.severi2@studio.unibo.it
*/

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
 * @brief Converts a byte array to an integer.
 */
int byteArrayToInt(const unsigned char* byteArray, size_t size);

/**
 * @brief Callback function for the MQTT connection.
 */
void callback(char* topic, byte* payload, unsigned int length);

MqttConnection* connection;
Components* hw;
int frequency;

void setup() {
	Serial.begin(115200);
	hw = new Components();
	hw->greenLed->off();
	hw->redLed->on();
	frequency = 0;
	// this need to be setted for the connection to the wifi
	const char* wifi_ssid = "iCereLan-FASTWEB";
	const char* wifi_password = "iLanVeloce";
	const char* mqtt_server = "192.168.178.31";
	int mqtt_port = 1883;
	const char* mqtt_topic_read = "monitoring-frequency";
	const char* mqtt_topic_send = "water-level";
	connection = new MqttConnection(wifi_ssid, wifi_password, mqtt_server, mqtt_port, mqtt_topic_read, mqtt_topic_send);
	connection->setCall(callback);
	connection->connect();
	hw->redLed->off();
	hw->greenLed->on();
}

void loop() {
	checkConnection();
	sendWaterLevel();
	delay(frequency);
}

void checkConnection() {
	if (!connection->getStatus()) {
		hw->greenLed->off();
		hw->redLed->on();
		connection->reconnectServer();
		hw->redLed->off();
		hw->greenLed->on();
	}
	connection->tick();
}

void sendWaterLevel() {
	char message[10];
	int waterLevel = CHANNEL_HEIGHT - hw->sonar->getDistance();
	sprintf(message, "%d", waterLevel);
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
	if (strcmp(topic, connection->getTopic()) == 0) {
		Serial.print("valore ricevuto: ");
		frequency = byteArrayToInt(payload, length);
		Serial.println(frequency);
	}
}

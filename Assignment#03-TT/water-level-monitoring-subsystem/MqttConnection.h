#ifndef __MQTTCONNECTION__
#define __MQTTCONNECTION__

#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <FS.h>

/**
 * Class used to manage the MQTT connection
 * it uses a json file to load the configuration
 * it should have this structure:
 * {
 *     "wifi_ssid": "your-ssid",
 *     "wifi_password": "your-password",
 *     "mqtt_server": "mqtt-server-ip",
 *     "mqtt_username": "your-mqtt-username",
 *     "mqtt_password": "your-mqtt-password",
 *     "mqtt_topic": "your-topic"
 * }
*/
class MqttConnection {
private:
    WiFiClient espClient;
    PubSubClient client(espClient);
    char* configFile;
    byte* messageReceived;
public:
    /**
     * Initialize the MQTT connection
     * @param configFile The path of the configuration file
    */
    MqttConnection(char* configFile);
    /**
     * Connect to the WiFi network
    */
    void connect();
    /**
     * Reconnect to the MQTT server
    */
    void reconnectServer();
    /**
     * Publishes a message to the MQTT server
     * @param message The message to publish
    */
    void sendMessagge(char* message);
    /**
     * Get the status of the MQTT connection
     * @return true if the connection is active, false otherwise
    */
    bool getStatus();
    /**
     * Get the last message received from the MQTT server
    */
    byte* getMessageReceived();
    /**
     * Tick the MQTT connection
    */
    void tick();
private:
    /**
     * Get the value of a key from the configuration file
    */
    String getConfigValue(const char *key);
    /**
     * Callback used to handle the messages from the MQTT server
    */
    static void callback(char* topic, byte* payload, unsigned int length);
};

#endif
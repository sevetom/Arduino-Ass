#ifndef __MQTTCONNECTION__
#define __MQTTCONNECTION__

#include <WiFi.h>
#include <PubSubClient.h>

/**
 * Class used to manage the MQTT connection
*/
class MqttConnection {
private:
    WiFiClient espClient;
    PubSubClient client;
    byte* messageReceived;
    const char* wifi_ssid;
    const char* wifi_password;
    const char* mqtt_server;
    int mqtt_port;
    const char* mqtt_topic;
public:
    /**
     * Initialize the MQTT connection
     * @param wifi_ssid The SSID of the WiFi network
     * @param wifi_password The password of the WiFi network
     * @param mqtt_server The IP address of the MQTT broker
     * @param mqtt_port The port of the MQTT broker
     * @param mqtt_topic The topic of the MQTT broker
    */
    MqttConnection(const char* wifi_ssid, const char* wifi_password, const char* mqtt_server, int mqtt_port, const char* mqtt_topic);
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
     * Callback used to handle the messages from the MQTT server
    */
    void callback(char* topic, byte* payload, unsigned int length);
    static void staticCallback(char* topic, byte* payload, unsigned int length, MqttConnection* instance);
};

#endif
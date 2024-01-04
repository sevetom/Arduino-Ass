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
    const char* mqtt_topic_read;
    const char* mqtt_topic_send;
public:
    /**
     * Initialize the MQTT connection
     * @param wifi_ssid The SSID of the WiFi network
     * @param wifi_password The password of the WiFi network
     * @param mqtt_server The IP address of the MQTT broker
     * @param mqtt_port The port of the MQTT broker
     * @param mqtt_topic_read The topic used to read
     * @param mqtt_topic_send The topic used to write
     * 
    */
    MqttConnection(const char* wifi_ssid, const char* wifi_password, const char* mqtt_server, int mqtt_port, const char* mqtt_topic_read, 
            const char* mqtt_topic_send);
    /**
     * Connect to the WiFi network
    */
    void connect();

    void setCall(std::function<void (char *, uint8_t *, unsigned int)> callback);
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

    char* getTopic();
};

#endif
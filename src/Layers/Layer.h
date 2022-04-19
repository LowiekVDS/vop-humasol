#pragma once
#include <stdint.h>
#include "ArduinoJson.h"
#include "Arduino.h"

#define BUFFER_SIZE 16

enum LoggingSeverity
{
    INFO,
    WARNING,
    ERROR
};

/**
 * @brief Abstract class to represent a network layer
 */
class Layer
{

protected:
    Layer *upLayer;
    Layer *downLayer;

public:
    String name;
    Layer() : upLayer(nullptr), downLayer(nullptr), name("Layer"){};
    ~Layer() {}

public:
    /**
     * @brief Processes an incoming packet and pushes the result to the layer above
     *
     * @param payload the payload to process
     * @param length  the length of said payload
     */
    virtual void up(uint8_t *payload, uint8_t length) = 0;

    /**
     * @brief Processes an outgoing packet and pushes the (wrapped) result to the layer below (if exists)
     *
     * @param payload the payload to wrap
     * @param length  the length of said payload
     */
    virtual void down(uint8_t *payload, uint8_t length) = 0;

    inline virtual bool step() { return false; };

    /**
     * @brief Loads a config (if required)
     *
     * @param jsonConfig
     */
    inline virtual void loadConfig(JsonObject *jsonConfig) { Serial.println("[LAYER] (WARNING)> loadConfig is not implemented"); };

    /**
     * @brief Set the upLayer object (the layer above this one)
     *
     * @param layer
     */
    inline void setUpLayer(Layer *layer) { this->upLayer = layer; };

    inline void log(uint8_t message, LoggingSeverity severity = INFO)
    {
        Serial.println("LOGGER");
        String severityString;

        if (severity == INFO)
        {
            severityString = "INFO";
        }
        else if (severity == WARNING)
        {
            severityString = "WARNING";
        }
        else if (severity == ERROR)
        {
            severityString = "ERROR";
        }

        Serial.printf("[%s] (%s)> ", this->name.c_str(), severityString.c_str());

        Serial.println(message);
    };

    inline void log(String message, LoggingSeverity severity = INFO)
    {
        this->log(message.c_str(), severity);
    };

    /**
     * @brief Set the downLayer object (the layer below this one)
     *
     * @param layer
     */
    inline void setDownLayer(Layer *layer) { this->downLayer = layer; };

    inline Layer *getDownLayer() { return this->downLayer; }

    inline Layer *getUpLayer() { return this->upLayer; }
};
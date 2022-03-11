#pragma once
#include <stdint.h>
#include "ArduinoJson.h"

/**
 * @brief Abstract class to represent a network layer
 */
class Layer
{

protected:
    Layer *upLayer;
    Layer *downLayer;

public:
    Layer() : upLayer(nullptr), downLayer(nullptr){};
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

    /**
     * @brief Loads a config (if required)
     *
     * @param jsonConfig
     */
    inline void loadConfig(JsonObject* jsonConfig){};

    /**
     * @brief Set the upLayer object (the layer above this one)
     *
     * @param layer
     */
    inline void setUpLayer(Layer *layer) { this->upLayer = layer; };

    /**
     * @brief Set the downLayer object (the layer below this one)
     *
     * @param layer
     */
    inline void setDownLayer(Layer *layer) { this->downLayer = layer; };

    inline Layer *getDownLayer() { return this->downLayer; }

    inline Layer *getUpLayer() { return this->upLayer; }
};
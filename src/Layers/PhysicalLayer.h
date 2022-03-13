#pragma once

#include "./Layer.h"
#include "TerminalLayer.h"
#include "stdint.h"
#include "ArduinoJson.h"
#if TARGET == ESP_32
#include <LoRa.h>
#include <stdlib.h>
#endif

/**
 * @brief The Physical layer. Basically a wrapper around the LoRa module.
 *
 * Implemented as a Singleton to simplify callback wrapping
 */

class PhysicalLayer : public BottomTerminalLayer
{

private:
    /**
     * @brief Pins and variables to init LoRa
     */
    long frequency = 0;
    int ssPin;
    int resetPin;
    int dio0Pin;

    /**
     * @brief Makes sure this class acts like a singleton
     */
    PhysicalLayer(void){};
    PhysicalLayer(const PhysicalLayer &) = delete;
    PhysicalLayer &operator=(const PhysicalLayer &) = delete;
    PhysicalLayer(PhysicalLayer &&) = delete;
    PhysicalLayer &operator=(PhysicalLayer &&) = delete;

public:
    /**
     * @brief Get the Instance object
     *
     * @return PhysicalLayer&
     */
    static PhysicalLayer &GetInstance()
    {
        static PhysicalLayer *singleton = new PhysicalLayer();
        singleton->name = "PHY";
        return *singleton;
    }

    /**
     * @brief Initializes LoRa. This must be called before sending any data or loading configurations
     *
     * @param frequency the operating frequency
     * @param ssPin
     * @param resetPin
     * @param dio0Pin the pin to register the interupt on
     */
    void init(long frequency, int ssPin = 5, int resetPin = 14, int dio0Pin = 2);

    /**
     * @brief Takes a json config to configure LoRa (spread factor, bandwidth, etc...)
     *
     * @param jsonConfig the configuration as json
     */
    void loadConfig(JsonObject *jsonConfig) override;

    void up(uint8_t *payload, uint8_t length) override;
    void down(uint8_t *payload, uint8_t length) override;

    /**
     * @brief The callback function for when LoRa receives messages
     *
     * @param packetSize the length of the received packet
     */
    static void OnReceive(int packetSize);
};
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
 * @brief The DummyPhysicalLayer layer. Basically a wrapper around the LoRa module.
 *
 * Implemented as a Singleton to simplify callback wrapping
 */

class DummyPhysicalLayer : public BottomTerminalLayer
{
public:
    void up(uint8_t *payload, uint8_t length) override;
    void down(uint8_t *payload, uint8_t length) override;

    /**
     * @brief The callback function for when LoRa receives messages
     *
     * @param packetSize the length of the received packet
     */
    void OnReceive(int packetSize);
};
#pragma once

#include "./Layer.h"
#include "TerminalLayer.h"
#include "stdint.h"
#include "ArduinoJson.h"
#if TARGET == ESP_32
#include <LoRa.h>
#endif

class PhysicalLayer : public BottomTerminalLayer
{

private:
    long frequency;
    int ssPin;
    int resetPin;
    int dio0Pin;

public:
    PhysicalLayer(long frequency, int ssPin = 5, int resetPin = 14, int dio0Pin = 2) : BottomTerminalLayer(), frequency(frequency), ssPin(ssPin), resetPin(resetPin), dio0Pin(dio0Pin)
    {
        LoRa.setPins(this->ssPin, this->resetPin, this->dio0Pin);

        if (!LoRa.begin(frequency))
            throw "LoRa initialization failed";
    };

    void loadConfig(JsonObject jsonConfig);

    void up(uint8_t *payload, uint8_t length) override;
    void down(uint8_t *payload, uint8_t length) override;

    
};
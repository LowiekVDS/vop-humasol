#pragma once

#include "./Layer.h"
#include "stdint.h"
#if TARGET == ESP_32
#include <LoRa.h>
#endif

class PhysicalLayer : public Layer
{

private:
    long frequency;
    int ssPin;
    int resetPin;
    int dio0Pin;

public:
    PhysicalLayer(long frequency, int ssPin = 5, int resetPin = 14, int dio0Pin = 2) : Layer(), frequency(frequency), ssPin(ssPin), resetPin(resetPin), dio0Pin(dio0Pin)
    {
        #if TARGET == ESP_32
        LoRa.setPins(this->ssPin, this->resetPin, this->dio0Pin);

        if (!LoRa.begin(frequency))
            throw "LoRa initialization failed";
        #endif
    };
    void up(uint8_t *payload, uint8_t length) override;
    void down(uint8_t *payload, uint8_t length) override;
};
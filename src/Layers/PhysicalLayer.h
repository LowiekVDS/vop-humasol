#pragma once

#include "./Layer.h"
#include "stdint.h"
#include <LoRa.h>

class PhysicalLayer : public virtual Layer
{

private:
    long frequency;
    int ssPin;
    int resetPin;
    int dio0Pin;

public:
    PhysicalLayer(long frequency, int ssPin = 5, int resetPin = 14, int dio0Pin = 2) : Layer(nullptr), frequency(frequency), ssPin(ssPin), resetPin(resetPin), dio0Pin(dio0Pin)
    {
        LoRa.setPins(this->ssPin, this->resetPin, this->dio0Pin);

        if (!LoRa.begin(frequency))
            throw "LoRa initialization failed";
    };
    void up(uint8_t *payload, int8_t length) override;
    void down(uint8_t *payload, int8_t length) override;
};
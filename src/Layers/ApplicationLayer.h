#pragma once
#include "Layer.h"

class ApplicationLayer : public Layer {
    public:
        void up(uint8_t *payload, uint8_t length) override;
        void down(uint8_t *payload, uint8_t length) override;
};
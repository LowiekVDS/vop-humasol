#pragma once
#include "Layer.h"

class TransportLayer : public Layer {
public:
    TransportLayer() : Layer() {};
public:
    void up(uint8_t* payload, uint8_t length);
    void down(uint8_t* payload, uint8_t length);
};
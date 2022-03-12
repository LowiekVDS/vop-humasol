#include "TransportLayer.h"

void TransportLayer::up(uint8_t* payload, uint8_t length)
{
    upLayer->up(payload, length);
};

void TransportLayer::down(uint8_t* payload, uint8_t length) {
    downLayer->down(payload, length);
};
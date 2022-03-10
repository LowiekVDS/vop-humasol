#include "ApplicationLayer.h"

void ApplicationLayer::up(uint8_t *payload, uint8_t length)
{
    // Process packet here!
}

void ApplicationLayer::down(uint8_t *payload, uint8_t length)
{
    downLayer->down(payload, length);
}
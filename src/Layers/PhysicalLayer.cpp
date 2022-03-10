#pragma once

#include <vector>
#include "PhysicalLayer.h"
#include "Layer.h"
#include "../Utils.h"


void PhysicalLayer::up(uint8_t *payload, uint8_t length)
{
    upLayer->up(payload, length);
}


void PhysicalLayer::down(uint8_t *payload , uint8_t length)
{
    // Actually send the thing to LoRa
    #if TARGET == ESP_32
    LoRa.beginPacket();
    LoRa.write(payload, length);
    LoRa.endPacket();
    #endif
    printArray(payload, length);
    // This one doesn't have a downlayer
}

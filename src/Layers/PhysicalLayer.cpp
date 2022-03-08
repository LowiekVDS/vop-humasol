#pragma once

#include <vector>
#include "PhysicalLayer.h"
#include "Layer.h"
#include <LoRa.h>

void PhysicalLayer::down(uint8_t *payload , int8_t length)
{
    // Actually send the thing to LoRa
    LoRa.beginPacket();
    LoRa.write(payload, length);
    LoRa.endPacket();
    
    // This one doesn't have a downlayer
}

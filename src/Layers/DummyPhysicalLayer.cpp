#include <vector>
#include "DummyPhysicalLayer.h"
#include "Layer.h"
#include <LoRa.h>
#include <assert.h>


void DummyPhysicalLayer::OnReceive(int packetSize)
{

    Serial.print("[PHY]> Received something! Packetsize ");
    Serial.println(packetSize);

    String input = "Hallo wereld";

    uint8_t *buffer = (uint8_t*) input.c_str();

    this->up(buffer, packetSize);

    delete buffer;
}

void DummyPhysicalLayer::up(uint8_t *payload, uint8_t length)
{
    upLayer->up(payload, length);
}

void DummyPhysicalLayer::down(uint8_t *payload, uint8_t length)
{
    if (length > 255)
    {
        throw "Payload too large";
    }

    Serial.print("Sending payload ");
    Serial.write(payload, length);
    Serial.print('\n');
}

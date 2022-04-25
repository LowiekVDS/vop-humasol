#include <vector>
#include "PhysicalLayer.h"
#include "Layer.h"
#include <LoRa.h>
#include <assert.h>
#include "Utils.h"

#include "Env.h"

void PhysicalLayer::init(long frequency, int ssPin, int resetPin, int dio0Pin)
{
    this->frequency = frequency;
    this->ssPin = ssPin;
    this->resetPin = resetPin;
    this->dio0Pin = dio0Pin;

    LoRa.setPins(this->ssPin, this->resetPin, this->dio0Pin);

    if (!LoRa.begin(frequency))
        throw "LoRa initialization failed";

    LoRa.onReceive(PhysicalLayer::OnReceive);
}

void PhysicalLayer::OnReceive(int packetSize)
{

    uint8_t *buffer = new uint8_t[packetSize];
    LoRa.readBytes(buffer, packetSize);

    PhysicalLayer::GetInstance().up(buffer, packetSize);

    delete buffer;
}

void PhysicalLayer::loadConfig(JsonObject *jsonConfig)
{

    assert(this->frequency);

    if (jsonConfig->containsKey("LoRaSpreadFactor"))
    {
        LoRa.setSpreadingFactor(std::atoi((*jsonConfig)["LoRaSpreadFactor"]));
    }
    if (jsonConfig->containsKey("txPower"))
    {
        LoRa.setTxPower(std::atoi((*jsonConfig)["txPower"]));
    }
    {
        LoRa.setSpreadingFactor(std::atoi((*jsonConfig)["LoRaSpreadFactor"]));
    }
    if (jsonConfig->containsKey("bandwidth"))
    {
        LoRa.setSignalBandwidth(static_cast<int>(std::atof((*jsonConfig)["bandwidth"]) * 1000));
    }
    if (jsonConfig->containsKey("codingRate"))
    {
        LoRa.setCodingRate4(std::atoi((*jsonConfig)["codingRate"]));
    }
    if (jsonConfig->containsKey("crc") && (*jsonConfig)["crc"] == "true")
    {
        LoRa.enableCrc();
    }
    else
    {
        LoRa.disableCrc();
    }
    if (jsonConfig->containsKey("type"))
    {
        if ((*jsonConfig)["type"] == "Receiver")
        {
            LoRa.receive();
        }
        else
        {
            LoRa.sleep();
        }
    }
}

void PhysicalLayer::up(uint8_t *payload, uint8_t length)
{
    assert(this->frequency);
    upLayer->up(payload, length);
}

void PhysicalLayer::down(uint8_t *payload, uint8_t length)
{

    if (DEBUG)
    {
        Serial.print("[PHY]> Sending packet, packetsize ");
        Serial.print(length);
        Serial.print(", data: ");
        printBuffer(payload, length);
    }
    assert(this->frequency);

    if (length > 255)
    {
        throw "Payload too large";
    }

    // Actually send the thing to LoRa
    LoRa.beginPacket();
    LoRa.write(payload, length);
    LoRa.endPacket();
}

#include <vector>
#include "PhysicalLayer.h"
#include "Layer.h"
#include "../Utils.h"

void PhysicalLayer::loadConfig(JsonObject jsonConfig)
{
    if (jsonConfig.containsKey("LoRaSpreadFactor"))
    {
        LoRa.setSpreadingFactor(std::atoi(jsonConfig["LoRaSpreadFactor"]));
    }
    if (jsonConfig.containsKey("txPower"))
    {
        LoRa.setTxPower(std::atoi(jsonConfig["txPower"]));
    }
    {
        LoRa.setSpreadingFactor(std::atoi(jsonConfig["LoRaSpreadFactor"]));
    }
    if (jsonConfig.containsKey("bandwidth"))
    {
        LoRa.setSignalBandwidth(static_cast<int>(std::atof(jsonConfig["bandwidth"]) * 1000));
    }
    if (jsonConfig.containsKey("codingRate"))
    {
        LoRa.setCodingRate4(std::atoi(jsonConfig["codingRate"]));
    }
    if (jsonConfig.containsKey("crc") && jsonConfig["crc"] == "true")
    {
        LoRa.enableCrc();
    }
    else
    {
        LoRa.disableCrc();
    }
}

void PhysicalLayer::up(uint8_t *payload, uint8_t length)
{
    upLayer->up(payload, length);
}

void PhysicalLayer::down(uint8_t *payload, uint8_t length)
{

    if (length > 255)
    {
        throw "Payload too large";
    }

    // Actually send the thing to LoRa
    LoRa.beginPacket();
    LoRa.write(payload, length);
    LoRa.endPacket();
}

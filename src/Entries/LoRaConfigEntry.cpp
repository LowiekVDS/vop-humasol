#include "LoRaConfigEntry.h"
#include "ArduinoJson.h"

void LoRaConfigEntry::encode(uint8_t *&pointer)
{
    TLVEntry::encode(pointer);

    *pointer = txPower;
    pointer += sizeof(uint8_t);
    *pointer = LoRaSpreadFactor;
    pointer += sizeof(uint8_t);
    *pointer = bandwidth;
    pointer += sizeof(long);
    *pointer = crc;
    pointer += sizeof(bool);
    *pointer = codingRate;
    pointer += sizeof(uint8_t);
}

void LoRaConfigEntry::decode(uint8_t *&pointer)
{
    TLVEntry::decode(pointer);

    txPower = *pointer;
    pointer += sizeof(uint8_t);
    LoRaSpreadFactor = *pointer;
    pointer += sizeof(uint8_t);
    bandwidth = *pointer;
    pointer += sizeof(long);
    crc = *pointer;
    pointer += sizeof(bool);
    codingRate = *pointer;
    pointer += sizeof(uint8_t);
}
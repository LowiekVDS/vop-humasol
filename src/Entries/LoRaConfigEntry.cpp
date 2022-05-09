#include "LoRaConfigEntry.h"
#include "ArduinoJson.h"

void LoRaConfigEntry::encode(uint8_t *&pointer)
{
    TLVEntry::encode(pointer);

    *pointer = txPower;
    pointer += sizeof(uint8_t);
    *pointer = LoRaSpreadFactor;
    pointer += sizeof(uint8_t);
    switch (bandwidth)
    {
    case 7800:
        *pointer = 0;
        break;
    case 10400:
        *pointer = 1;
        break;
    case 15600:
        *pointer = 2;
        break;
    case 20800:
        *pointer = 3;
        break;
    case 31200:
        *pointer = 4;
        break;
    case 41700:
        *pointer = 5;
        break;
    case 62500:
        *pointer = 6;
        break;
    case 125000:
    default:
        *pointer = 7;
        break;
    case 250000:
        *pointer = 8;
        break;
    case 500000:
        *pointer = 9;
        break;
    }

    pointer++;

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

    switch (*pointer)
    {
    case 0:
        bandwidth = 7800;
        break;
    case 1:
        bandwidth = 10400;
        break;
    case 2:
        bandwidth = 15600;
        break;
    case 3:
        bandwidth = 20800;
        break;
    case 4:
        bandwidth = 31200;
        break;
    case 5:
        bandwidth = 41700;
        break;
    case 6:
        bandwidth = 62500;
        break;
    case 7:
    default:
        bandwidth = 125000;
        break;
    case 8:
        bandwidth = 250000;
        break;
    case 9:
        bandwidth = 500000;
        break;
    }

    pointer += sizeof(uint8_t);

    crc = *pointer;
    pointer += sizeof(bool);
    codingRate = *pointer;
    pointer += sizeof(uint8_t);
}
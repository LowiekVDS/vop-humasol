#pragma once

#include <stdint.h>
#include <stdio.h>
#include "TLVEntry.h"
#include "./Type.h"
#include "ArduinoJson.h"

struct LoRaConfigEntry : public TLVEntry
{
public:
    uint8_t txPower;
    uint8_t LoRaSpreadFactor;
    long bandwidth;
    bool crc;
    uint8_t codingRate;

public:
    LoRaConfigEntry(uint8_t txPower = 15, uint8_t LoRaSpreadFactor = 11, long bandwidth = 125, bool crc = false, uint8_t codingRate = 5)
        : TLVEntry(LORA_CONFIG, 3 * sizeof(uint8_t) + sizeof(long) + sizeof(bool)), txPower(txPower), LoRaSpreadFactor(LoRaSpreadFactor), bandwidth(bandwidth), crc(crc), codingRate(codingRate){};
    ~LoRaConfigEntry(){};

public:
    void encode(uint8_t *&pointer) override;
    void decode(uint8_t *&pointer) override;

public:
    int size() override { return sizeof(type) + sizeof(length) + length; };

public:
    void print(char end = ' ') override{};
};
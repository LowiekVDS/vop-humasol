#pragma once

#include <stdint.h>
#include <stdio.h>
#include "TLVEntry.h"
#include "./Type.h"
#include "ArduinoJson.h"

struct BatteryLevelEntry : public TLVEntry
{
public:
    uint8_t level;

public:
    BatteryLevelEntry(uint8_t level = 0) : TLVEntry(BATTERY_LEVEL, 1), level(level){};
    ~BatteryLevelEntry(){};

public:
    void encode(uint8_t *&pointer) override;
    void decode(uint8_t *&pointer) override;

public:
    int size() override { return sizeof(type) + sizeof(length) + length; };

public:
    void print(char end = ' ') override
    {
        log("Type: %s\nLength: %d\nLevel: %d\n%c", "BatteryLevelEntry", (uint8_t)this->length, (uint8_t)this->level, end);
    }
};
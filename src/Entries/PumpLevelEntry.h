#pragma once
#include "Type.h"
#include <stdint.h>
#include <stdio.h>
#include "TLVEntry.h"
#include "ArduinoJson.h"

struct PumpLevelEntry : public TLVEntry
{
public:
    uint8_t level;

    PumpLevelEntry(uint8_t level = 0) : TLVEntry(PUMP_LEVEL, 1), level(level){};
    ~PumpLevelEntry(){};

    void encode(uint8_t *&pointer) override;
    void decode(uint8_t *&pointer) override;

    int size() override { return sizeof(type) + sizeof(length) + sizeof(level); };

public:
    void print(char end = ' ') override
    {
        log("Type: %s\nLength: %d\nLevel: %d\n%c", "PumpLevelEntry", (uint8_t)this->length, (uint8_t)this->level, end);
    }
};
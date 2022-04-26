#pragma once
#include "Type.h"
#include <stdint.h>
#include <stdio.h>
#include "TLVEntry.h"
#include "ArduinoJson.h"

struct PumpOffEntry : public TLVEntry
{
public:
    PumpOffEntry() : TLVEntry(PUMP_OFF, 1){};
    ~PumpOffEntry(){};

    int size() override { return sizeof(type) + sizeof(length) + 1; };

    void print(char end = ' ') override
    {
        log("Type: %s\nLength: %d\n", "PumpOffEntry", (uint8_t)this->length, end);
    }
};
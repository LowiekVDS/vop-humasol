#pragma once
#include "Type.h"
#include <stdint.h>
#include <stdio.h>
#include "TLVEntry.h"
#include "ArduinoJson.h"

struct PumpOnEntry : public TLVEntry
{
public:
    PumpOnEntry() : TLVEntry(PUMP_ON, 1){};
    ~PumpOnEntry(){};

    int size() override { return sizeof(type) + sizeof(length) + 1; };

    void print(char end = ' ') override
    {
        log("Type: %s\nLength: %d\n", "PumpOnEntry", (uint8_t)this->length, end);
    }
};
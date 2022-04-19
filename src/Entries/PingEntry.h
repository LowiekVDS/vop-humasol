#pragma once
#include "Type.h"
#include <stdint.h>
#include <stdio.h>
#include "TLVEntry.h"
#include "ArduinoJson.h"

struct PingEntry : public TLVEntry
{
public:
    PingEntry() : TLVEntry(PING, 1){};
    ~PingEntry(){};
    TLVEntry *process(JsonObject *configuration) override;

    int size() override { return sizeof(type) + sizeof(length) + 1; };

    void print(char end = ' ') override
    {
        log("Type: %s\nLength: %d\n", "PingEntry", (uint8_t)this->length, end);
    }
};
#pragma once
#include "Type.h"
#include <stdint.h>
#include <stdio.h>
#include "TLVEntry.h"
#include "ArduinoJson.h"

struct PongEntry : public TLVEntry
{
public:
    PongEntry(uint8_t level = 0) : TLVEntry(PONG, 1){};
    ~PongEntry(){};
    TLVEntry *process(JsonObject *configuration) override;

    int size() override { return sizeof(type) + sizeof(length) + 1; };

    void print(char end = ' ') override
    {
        log("Type: %s\nLength: %d\n", "PongEntry", (uint8_t)this->length, end);
    }
};
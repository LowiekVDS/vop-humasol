#pragma once
#include "Type.h"
#include <stdint.h>
#include <stdio.h>
#include "TLVEntry.h"
#include "ArduinoJson.h"

struct PongEntry : public TLVEntry
{
public:
    PongEntry() : TLVEntry(PONG, 0){};
    ~PongEntry(){};

    int size() override { return sizeof(type) + sizeof(length); };

    void print(char end = ' ') override
    {
        log("Type: %s\nLength: %d\n", "PongEntry", (uint8_t)this->length, end);
    }
};
#pragma once
#include "Type.h"
#include <stdint.h>
#include <stdio.h>
#include "TLVEntry.h"
struct PumpLevelEntry : public TLVEntry{
    public:
        uint8_t length;
        uint8_t level;
    public:
        PumpLevelEntry(uint8_t level = 0): TLVEntry(PUMP_LEVEL), length(1), level(level){};

    int size() override { return sizeof(type) + sizeof(length) + sizeof(level);};
    
    public:
        void print() {
            printf("Type: %s\nLength: %d\nLevel: %d\n", "PumpLevelEntry", (uint8_t)this->length, (uint8_t)this->level);
        } 
};
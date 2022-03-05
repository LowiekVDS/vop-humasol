#pragma once

#include <stdint.h>
#include <stdio.h>
#include "TLVEntry.h"
#include "./Type.h"

struct BatteryLevelEntry : public TLVEntry{
    public:
        uint8_t length;
        uint8_t level;
    public:
        BatteryLevelEntry(uint8_t level = 0): TLVEntry(BATTERY_LEVEL), length(1), level(level) {};

    public:
        int size() override { return sizeof(type) + sizeof(length) + length;};

    public:
        void print() {
            printf("Type: %s\nLength: %d\nLevel: %d\n", "BatteryLevelEntry", (uint8_t)this->length, (uint8_t)this->level);
        } 

};
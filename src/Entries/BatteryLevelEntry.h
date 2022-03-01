#pragma once

#include "TLVEntry.h"
#include <stdint.h>

class BatteryLevelEntry : public TLVEntry {
    private:
        uint8_t level;
    public:
        BatteryLevelEntry(uint8_t level) : TLVEntry(Type::BATTERY_LEVEL, 1), level(level) {};

};
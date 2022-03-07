#pragma once
#include <stdint.h>

#define BATTERY_LEVEL 1
#define PUMP_LEVEL 2
#define PUMP_STATE 3

inline bool isType(uint8_t type) {
    return (type>=BATTERY_LEVEL) && (type <= PUMP_STATE);
};
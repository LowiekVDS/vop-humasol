#pragma once
#include <stdint.h>

#define BATTERY_LEVEL 0b0001 // 1
#define PUMP_LEVEL 0b0010 // 2
#define PUMP_STATE 0b0011 // 3
#define PING 0b0100 // 4
#define PONG 0b0101 // 5

inline bool isType(uint8_t type) {
    return (type>=BATTERY_LEVEL) && (type <= PONG);
};
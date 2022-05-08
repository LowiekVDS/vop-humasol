#pragma once
#include <stdint.h>

#define BATTERY_LEVEL 0b0001 // 1
#define PUMP_LEVEL 0b0010 // 2
#define PUMP_STATE 0b0011 // 3
#define PING 0b0100 // 4
#define PONG 0b0101 // 5
#define LORA_FEEDBACK 0b0110 
#define LORA_CONFIG 0b0111
#define CONFIG 0b1000

inline bool isType(uint8_t type) {
    return (type>=BATTERY_LEVEL) && (type <= CONFIG);
};
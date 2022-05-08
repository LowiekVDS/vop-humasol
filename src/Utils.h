#pragma once
#include "Constants.h"
#include <cstdarg>

#if TARGET == WINDOWS
#include <cstdio>
#elif TARGET == ESP_32
#include <Arduino.h> // For Serial
#endif

inline void logInit()
{
#if TARGET == ESP_32
    Serial.begin(SERIAL_BAUD_RATE);
#endif
}

inline String convertToString(uint8_t* a, int size)
{
    int i;
    String s = "";
    for (i = 0; i < size; i++) {
        s = s + a[i];
    }
    return s;
}

inline void printBuffer(uint8_t* payload, uint8_t length) {
    for (auto i = 0; i < length; i++)
    {
        Serial.print(payload[i], HEX);
        Serial.print(' ');
    }
    Serial.println();
}

inline void log(const char* format, ...)
{
    #if TARGET == WINDOWS
    va_list vl;
    va_start(vl, format);
    vprintf(format, vl);
    va_end(vl);
    #else
    Serial.printf(format); // TODO: Fix this!!
    #endif
}
/* Rounds 'numToRound' to closest multiple of 'multiple' greater or equal to itself */ 
inline int roundUp(int numToRound, int multiple)
{
    if (multiple == 0)
        return numToRound;

    int remainder = numToRound % multiple;
    if (remainder == 0)
        return numToRound;

    return numToRound + multiple - remainder;
}

inline void printArray(void* array, int length){
    uint8_t* pointer = (uint8_t*) array;
    for (int i = 0; i < length; i++){
        // printf("0x%02x ", pointer[i]);
        Serial.printf("0x%02x ", pointer[i]);
    }
} 
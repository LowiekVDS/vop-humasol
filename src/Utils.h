#pragma once
#include "Constants.h"
#include <cstdarg>

#if TARGET == GCC
#include <cstdio>
#elif TARGET == ESP32
#include <Arduino.h> // For Serial
#endif

inline void logInit()
{
#if TARGET == ESP32
    Serial.begin(SERIAL_BAUD_RATE);
#endif
}

inline void log(const char* format, ...)
{
    #if TARGET == GCC
    va_list vl;
    va_start(vl, format);
    vprintf(format, vl);
    va_end(vl);
    #else
    Serial.printf(format);
    #endif
}
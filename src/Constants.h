#pragma once

#define MAX_PACKET_LENGTH 250

#define GCC 0
#define ESP32 1
#ifndef TARGET 
#define TARGET ESP32
#endif

#define SERIAL_BAUD_RATE 9600
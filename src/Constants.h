#pragma once

#define MAX_PACKET_LENGTH 250

#define GCC 0
#define ESP32 1
#ifndef TARGET 
#define TARGET ESP32
#endif

#define SERIAL_BAUD_RATE 9600

#define ENCRYPTION 1
#define AES_KEY { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f }
#define AES_IV AES_KEY // TODO: Should be randomly generated!!!!

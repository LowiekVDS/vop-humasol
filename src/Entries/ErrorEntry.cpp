#include "./ErrorEntry.h"
#include "ArduinoJson.h"

void ErrorEntry::encode(uint8_t *&pointer)
{
    TLVEntry::encode(pointer);

    for (uint8_t i = 0; i < length; i++)
    {
        *pointer = payload[i];
        pointer++;
    }
}

void ErrorEntry::decode(uint8_t *&pointer)
{
    TLVEntry::decode(pointer);

    payload = new uint8_t[length] {0};

    for (uint8_t i = 0; i < length; i++)
    {
        payload[i] = *pointer;
        pointer++;
    }
}
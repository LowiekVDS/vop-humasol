#include "./PumpStateEntry.h"
#include "ArduinoJson.h"

void PumpStateEntry::encode(uint8_t *&pointer)
{
    TLVEntry::encode(pointer);

    *pointer = state;
    pointer++;
}

void PumpStateEntry::decode(uint8_t *&pointer)
{
    TLVEntry::decode(pointer);

    state = *pointer;
    pointer++;
}
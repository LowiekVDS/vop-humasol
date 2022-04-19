#include "BatteryLevelEntry.h"
#include "ArduinoJson.h"

void BatteryLevelEntry::encode(uint8_t *&pointer)
{
    TLVEntry::encode(pointer);

    *pointer = level;
    pointer++;
}

void BatteryLevelEntry::decode(uint8_t *&pointer)
{
    TLVEntry::decode(pointer);

    level = *pointer;
    pointer++;
}
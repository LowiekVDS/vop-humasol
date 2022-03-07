#include "TLVEntry.h"
#include "Entries.h"

TLVEntry *TLVEntry::CreateFromType(uint8_t type)
{

    switch (type)
    {
    case BATTERY_LEVEL:
    {
        BatteryLevelEntry *bat = new BatteryLevelEntry();
        return (TLVEntry *)bat;
    }
    case PUMP_LEVEL:
    {
        PumpLevelEntry *pump = new PumpLevelEntry();
        return (TLVEntry *)pump;
    }
    case PUMP_STATE:
    {
        PumpStateEntry *pump = new PumpStateEntry();
        return (TLVEntry *) pump;
    }
    default:
    {
        return nullptr;
    }
    }
}

void TLVEntry::encode(uint8_t *&pointer)
{
    *pointer = type;
    pointer++;

    *pointer = length;
    pointer++;
}

void TLVEntry::decode(uint8_t *&pointer)
{
    this->type = *pointer; // todo: ASSERT THIS IS CORRECT WITH ACTUAL VALUE
    pointer++;

    this->length = *pointer; // todo: ASSERT THIS IS CORRECT WITH ACTUAL VALUE
    pointer++;
}

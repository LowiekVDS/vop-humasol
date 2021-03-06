#include "TLVEntry.h"
#include "Entries.h"
#include <stdexcept>

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
        return (TLVEntry *)pump;
    }
    case PING:
    {
        PingEntry *ping = new PingEntry();
        return (TLVEntry *)ping;
    }
    case PONG:
    {
        PongEntry *pong = new PongEntry();
        return (TLVEntry *)pong;
    }
    case LORA_FEEDBACK:
    {
        LoRaFeedbackEntry *pong = new LoRaFeedbackEntry();
        return (TLVEntry *)pong;
    }
    case LORA_CONFIG:
    {
        LoRaConfigEntry *pong = new LoRaConfigEntry();
        return (TLVEntry *)pong;
    }
    case CONFIG:
    {
        ConfigEntry *pong = new ConfigEntry();
        return (TLVEntry *)pong;
    }
    case TRANSPORTLAYER_E:
    {
        ErrorEntry *pong = new ErrorEntry();
        return (TLVEntry *)pong;
    }
    default:
    {
        Serial.println("*TLVEntry::CreateFromType > Received unvalid type");
        throw std::invalid_argument("*TLVEntry::CreateFromType > Received unvalid type");
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

#include "ConfigEntry.h"
#include "ArduinoJson.h"

ConfigEntry::ConfigEntry(uint8_t *typePtr, uint8_t *passwordPtr) : TLVEntry(CONFIG, (5 + 16) * sizeof(uint8_t))
{
    if (typePtr)
    {
        memcpy(this->type, typePtr, 5);
    }
    if (passwordPtr)
    {
        memcpy(this->password, passwordPtr, 16);
    }
}

void ConfigEntry::encode(uint8_t *&pointer)
{
    TLVEntry::encode(pointer);

    for (uint8_t i = 0; i < 5; i++)
    {
        *pointer = type[i];
        pointer++;
    }
    for (uint8_t i = 0; i < 16; i++)
    {
        *pointer = password[i];
        pointer++;
    }
}

void ConfigEntry::decode(uint8_t *&pointer)
{
    TLVEntry::decode(pointer);

    printBuffer(pointer, 21);

    for (uint8_t i = 0; i < 5; i++)
    {
        Serial.println(*pointer, HEX);
        type[i] = *pointer;
        pointer++;
    }
    for (uint8_t i = 0; i < 16; i++)
    {
        password[i] = *pointer;
        pointer++;
    }
}
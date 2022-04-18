#include "PumpLevelEntry.h"
#include "ArduinoJson.h"

void PumpLevelEntry::encode(uint8_t *&pointer)
{
    TLVEntry::encode(pointer);

    *pointer = level;
    pointer++;
}

void PumpLevelEntry::decode(uint8_t *&pointer)
{
    TLVEntry::decode(pointer);

    level = *pointer;
    pointer++;
}

TLVEntry* PumpLevelEntry::process(JsonObject* configuration)
{
    if (this->level>85){
        log("Pumping halted.\n");
    }

    return nullptr;
}
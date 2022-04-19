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

TLVEntry* PumpStateEntry::process(JsonObject* configuration)
{
    if (this->state == PUMP_CLOSE){
        log("Pumping halted!\n");
    } else if (this->state == PUMP_OPEN) {
        log("Pumping pending...\n");
    }

    return nullptr;
}
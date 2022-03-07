#include "./PumpStateEntry.h"

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

void PumpStateEntry::process()
{
    if (this->state == PUMP_CLOSE){
        log("Pumping halted!\n");
    } else if (this->state == PUMP_OPEN) {
        log("Pumping pending...\n");
    }
}
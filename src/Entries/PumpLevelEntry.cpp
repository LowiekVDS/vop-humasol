#include "PumpLevelEntry.h"
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

void PumpLevelEntry::process()
{
    if (this->level>85){
        log("Pumping halted.\n");
    }
}
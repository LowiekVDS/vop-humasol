#include "Receiver.h"
#include <stdint.h>
#include "Constants.h"
#include "./Entries/Type.h"
#include "./Entries/TLVEntry.h"
#include <iostream>

void Receiver::parse(uint8_t* buffer, uint8_t payloadSize) {
    
    uint8_t* pointer = &buffer[0];

    while ((pointer-buffer)<payloadSize){
        TLVEntry* e = TLVEntry::CreateFromType(*pointer);
        e->decode(pointer);
        m_entries.push_back(e);

        e->print('\n');
    }

    
}

void Receiver::process() {
    for (auto it = m_entries.begin(); it != m_entries.end(); ){
        TLVEntry* entry = *it;
        entry->process();
        it = m_entries.erase(it);
    }
}
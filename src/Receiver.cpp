#include "Receiver.h"
#include <stdint.h>
#include "Constants.h"
#include "./Entries/Type.h"
#include "./Entries/TLVEntry.h"
#include "./Encryption/AES.h"
#include <iostream>

void Receiver::decrypt()
{
    
}

void Receiver::parse()
{

    decrypt();

    uint8_t *pointer = &m_buffer[0];

    while ((pointer - m_buffer) < m_bufferSize)
    {
        if (!isType(*pointer))
            break;

        TLVEntry *e = TLVEntry::CreateFromType(*pointer);
        e->decode(pointer);
        m_entries.push_back(e);

        e->print('\n');
    }
}

void Receiver::process()
{
    for (auto it = m_entries.begin(); it != m_entries.end();)
    {
        TLVEntry *entry = *it;
        entry->process(nullptr);
        it = m_entries.erase(it);
    }
}
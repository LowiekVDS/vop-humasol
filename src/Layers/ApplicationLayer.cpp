#include "ApplicationLayer.h"

void ApplicationLayer::up(uint8_t *payload, uint8_t length)
{
    extractEntries(payload, length);

    for (auto it = m_entries.begin(); it != m_entries.end();)
    {
        TLVEntry *entry = *it;
        entry->process(); // This should be implemented in each Entry class and dispatch its changes to the appropriate handler
        it = m_entries.erase(it);
    }
}

void ApplicationLayer::down(uint8_t *payload, uint8_t length)
{
    downLayer->down(payload, length);
}

void ApplicationLayer::extractEntries(uint8_t *payload, uint8_t length) {
    
    uint8_t *pointer = &payload[0];

    while ((pointer - payload) < length)
    {
        if (!isType(*pointer))
            break;

        TLVEntry *e = TLVEntry::CreateFromType(*pointer);
        e->decode(pointer);
        m_entries.push_back(e);
    }
}
#include "ApplicationLayer.h"
#include "Entries/TLVEntry.h"
#include "ArduinoJson.h"
#include <vector>

void ApplicationLayer::up(uint8_t *payload, uint8_t length)
{
    std::vector<TLVEntry *> entries = ApplicationLayer::extractEntries(payload, length);

    for (auto it = entries.begin(); it != entries.end();)
    {
        TLVEntry *entry = *it;
        entry->process(); // This should be implemented in each Entry class and dispatch its changes to the appropriate handler
        it = entries.erase(it);
    }
}

void ApplicationLayer::loadConfig(JsonObject jsonConfig) {
    // TODO set something up with handlers? Idk
}

void ApplicationLayer::down(uint8_t *payload, uint8_t length)
{
    downLayer->down(payload, length);
}

void ApplicationLayer::addEntry(TLVEntry *entry)
{
    m_entries.push_back(entry);
    m_bufferSize += entry->size();
}

bool ApplicationLayer::step() {
    // Check all messages
    
}

void ApplicationLayer::flush()
{
    uint8_t *payload = new uint8_t[m_bufferSize]{0}; // Sets buffer to 0;
    uint8_t *pointer = &payload[0];

    auto it = m_entries.begin();

    while (it != m_entries.end())
    {
        TLVEntry *entry = *it;
        entry->encode(pointer);
        delete entry;
        it = m_entries.erase(it);
    }

    this->down(payload, m_bufferSize);

    // Now clear the buffer
    this->m_bufferSize = 0;
}

std::vector<TLVEntry *> ApplicationLayer::extractEntries(uint8_t *payload, uint8_t length)
{

    uint8_t *pointer = &payload[0];

    std::vector<TLVEntry *> entries;

    while ((pointer - payload) < length)
    {
        if (!isType(*pointer))
            break;

        TLVEntry *e = TLVEntry::CreateFromType(*pointer);
        e->decode(pointer);
        entries.push_back(e);
    }

    return entries;
}
#include "ApplicationLayer.h"
#include "Entries/TLVEntry.h"
#include "ArduinoJson.h"
#include <vector>

void ApplicationLayer::loadConfig(JsonObject *jsonConfig)
{
    this->configuration = jsonConfig;
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

void ApplicationLayer::flush()
{

    if (m_bufferSize == 0)
        return;

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
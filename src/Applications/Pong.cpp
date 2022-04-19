#include "Pong.h"
#include "../Layers/ApplicationLayer.h"
#include "../Entries/Type.h"
#include "../Entries/TLVEntry.h"

void PongApp::up(uint8_t *payload, uint8_t length)
{
    std::vector<TLVEntry *> entries = ApplicationLayer::extractEntries(payload, length);

    this->flush();

    for (auto it = entries.begin(); it != entries.end();)
    {
        TLVEntry *entry = *it;

        if (entry->type == PING)
        {
            this->addEntry(TLVEntry::CreateFromType(PONG));
        }
        it = entries.erase(it);
    }

    this->flush();
}
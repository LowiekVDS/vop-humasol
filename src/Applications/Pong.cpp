#include "Pong.h"
#include "../Layers/ApplicationLayer.h"
#include "../Entries/Type.h"
#include "../Entries/TLVEntry.h"
#include "../Layers/PhysicalLayer.h"
#include "LoRa.h"

void PongApp::up(uint8_t *payload, uint8_t length)
{
    std::vector<TLVEntry *> entries = ApplicationLayer::extractEntries(payload, length);

    for (auto it = entries.begin(); it != entries.end();)
    {
        TLVEntry *entry = *it;

        if (entry->type == PING)
        {
            this->addEntry(TLVEntry::CreateFromType(PONG));
        } else {
            Serial.println("[PongApp]> Entry is not pong");
        }
        it = entries.erase(it);
    }

    this->flush();
}

bool PongApp::step() {
    LoRa.receive();
    return false; 
}
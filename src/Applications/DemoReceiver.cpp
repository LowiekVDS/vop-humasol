#include "DemoReceiver.h"
#include "../Layers/ApplicationLayer.h"
#include "../Entries/Type.h"
#include "../Entries/TLVEntry.h"
#include "../Entries/PumpOff.h"
#include "../Entries/PumpOn.h"
#include "Env.h"
#include "../Layers/PhysicalLayer.h"
#include "LoRa.h"

void DemoReceiverApp::up(uint8_t *payload, uint8_t length)
{
    std::vector<TLVEntry *> entries = ApplicationLayer::extractEntries(payload, length);
    for (auto it = entries.begin(); it != entries.end();)
    {
        TLVEntry *entry = *it;

        if (entry->type == PUMP_OFF) {
            digitalWrite(26, 0);
        } else if(entry->type == PUMP_ON) {
            digitalWrite(26, 1);
        }
 
        it = entries.erase(it);
    }
}

bool DemoReceiverApp::step()
{
    LoRa.receive();
    return false;
}
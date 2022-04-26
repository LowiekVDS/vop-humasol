#include "DemoTransmitter.h"
#include "../Layers/ApplicationLayer.h"
#include "../Entries/Type.h"
#include "../Entries/TLVEntry.h"
#include "../Entries/PumpOff.h"
#include "../Entries/PumpOn.h"
#include "Env.h"
#include "../Layers/PhysicalLayer.h"
#include "LoRa.h"

void DemoTransmitterApp::up(uint8_t *payload, uint8_t length)
{
    std::vector<TLVEntry *> entries = ApplicationLayer::extractEntries(payload, length);
    for (auto it = entries.begin(); it != entries.end();)
    {
        it = entries.erase(it);
    }
}

bool DemoTransmitterApp::step()
{

    if (millis() - this->timeSent > this->SEND_INTERVAL)
    {
        this->timeSent = millis();

        if (digitalRead(27))
        {
            this->addEntry(new PumpOnEntry());
        }
        else
        {
            this->addEntry(new PumpOffEntry());
        }
        this->flush();
    }

}
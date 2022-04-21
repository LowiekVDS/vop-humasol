#include "DispatcherApp.h"
#include "../Entries/Entries.h"
#define SEND_INTERVAL 30000 // In ms

bool DispatcherApp::step()
{
    if (millis() - m_lastSent > SEND_INTERVAL)
    {
        m_lastSent = millis();

        runPump();
        runBattery();
        this->flush();
    }
}

void DispatcherApp::runPump()
{
    uint8_t level = 79;

    TLVEntry *entry = new PumpStateEntry(PUMP_OPEN); // TODO: Actually read the state from the pump
    this->addEntry(entry);
}

void DispatcherApp::runBattery()
{
    uint8_t bat_level = 23;

    TLVEntry *entry = new BatteryLevelEntry(bat_level); // TODO: Actually read the level from the battery
    this->addEntry(entry);
}
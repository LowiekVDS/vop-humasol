#include "DispatcherApp.h"
#include "../Entries/Entries.h"
#define SEND_INTERVAL 1000 // In ms

#define PIN_PUMP_RELAY 20

bool DispatcherApp::run() {
    if (millis()-m_lastSent > SEND_INTERVAL) {
        m_lastSent = millis();

        
        runPump();
        runBattery();
        this->flush();
    }
}

void DispatcherApp::runPump() {
    int switch_value = digitalRead(PIN_PUMP_RELAY);
    

    TLVEntry* entry = new PumpStateEntry(switch_value?PUMP_CLOSE:PUMP_OPEN); // TODO: Actually read the state from the pump
    this->addEntry(entry);

}

void DispatcherApp::runBattery() {
    uint8_t bat_level = 23;

    TLVEntry* entry = new BatteryLevelEntry(bat_level); // TODO: Actually read the level from the battery
    this->addEntry(entry);
}
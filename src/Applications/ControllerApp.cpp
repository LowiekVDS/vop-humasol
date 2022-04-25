#include "ControllerApp.h"

void ControllerApp::up(uint8_t* payload, uint8_t length) {
    std::vector<TLVEntry *> entries = ApplicationLayer::extractEntries(payload, length);

    for (auto it = entries.begin(); it != entries.end();)
    {
        TLVEntry *entry = *it;

        // Pump State Entry
        if (entry->type == PUMP_STATE){
            PumpStateEntry* pumpStateEntry = (PumpStateEntry*)entry;

            if (pumpStateEntry->state == PUMP_OPEN){
                this->m_newPumpState = PumpState::OPEN;
            } else if (pumpStateEntry->state==PUMP_CLOSE){
                this->m_newPumpState = PumpState::CLOSED;
            }
        }

        // Pump State Entry
        else if (entry->type == PUMP_LEVEL){
            PumpLevelEntry* pumpLevelEntry = (PumpLevelEntry*)entry;

            if (pumpLevelEntry->level > 90){
                this->m_newPumpState = PumpState::CLOSED;
            } else {
                this->m_newPumpState = PumpState::OPEN;
            }
        }
        delete entry;
    }

    this->flush();
}

bool ControllerApp::step() {
    if (this->m_newPumpState != this->m_pumpState){
        this->m_pumpState = this->m_newPumpState;
        digitalWrite(15, m_pumpState); // TODO: Select the appropriate pin
    }
}
#include "ControllerApp.h"
#include "Arduino.h"
#include <LoRa.h>
void ControllerApp::up(uint8_t* payload, uint8_t length) {
    std::vector<TLVEntry *> entries = ApplicationLayer::extractEntries(payload, length);

    for (auto it = entries.begin(); it != entries.end();)
    {
        TLVEntry *entry = *it;
        Serial.println("Received Entry");

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
        it = entries.erase(it);
    }
}

bool ControllerApp::step() {
    LoRa.receive();
    // Serial.println("Step Controller");

    // if (this->m_newPumpState != this->m_pumpState){
    //     if (m_newPumpState == PumpState::OPEN){
    //         if (m_pumpState == PumpState::OPEN){
    //             Serial.println("Still Pumping");
    //         } else {
    //             Serial.println("Started Pumping");
    //         }
    //     } else if (m_newPumpState == PumpState::CLOSED){
    //         if (m_pumpState == PumpState::CLOSED){
    //             Serial.println("Still not Pumping");
    //         } else {
    //             Serial.println("Stopped Pumping");
    //         }
    //     }
    //     this->m_pumpState = this->m_newPumpState;
    //     digitalWrite(GPIO_NUM_34, m_pumpState);
    // }

    digitalWrite(GPIO_NUM_32, !this->m_newPumpState);
    return true;
}
#include "ControllerApp.h"
#include "Arduino.h"
#include <LoRa.h>

void ControllerApp::loadConfig(JsonObject* config) {
    if (config->containsKey("controllerPinPump"))
    {
        this->prm_pin_pump = std::atoi((*config)["controllerPinPump"]);
    }
    if (config->containsKey("controllerSafetymodeInitTimeout"))
    {
        this->prm_safety_mode_init_timeout = std::atoi((*config)["controllerSafetymodeInitTimeout"]);
    }
    if (config->containsKey("controllerSafetymodePumpingPeriod"))
    {
        this->prm_safety_mode_pumping_period = std::atoi((*config)["controllerSafetymodePumpingPeriod"]);
    }
     if (config->containsKey("controllerSafetymodeRestingPeriod"))
    {
        this->prm_safety_mode_resting_period = std::atoi((*config)["controllerSafetymodeRestingPeriod"]);
    }
    if (config->containsKey("controllerInvert"))
    {
        this->prm_invert = (*config)["controllerInvert"] == "true";
    }
}

void ControllerApp::up(uint8_t *payload, uint8_t length)
{
    std::vector<TLVEntry *> entries = ApplicationLayer::extractEntries(payload, length);

    for (auto it = entries.begin(); it != entries.end();)
    {
        TLVEntry *entry = *it;
        Serial.println("Received Entry");

        // Pump State Entry
        if (entry->type == PUMP_STATE)
        {
            PumpStateEntry *pumpStateEntry = (PumpStateEntry *)entry;

            if (pumpStateEntry->state == PUMP_OPEN)
            {
                this->m_newPumpState = PumpState::OPEN;
            }
            else if (pumpStateEntry->state == PUMP_CLOSE)
            {
                this->m_newPumpState = PumpState::CLOSED;
            }
        }

        // Pump State Entry
        else if (entry->type == PUMP_LEVEL)
        {
            PumpLevelEntry *pumpLevelEntry = (PumpLevelEntry *)entry;

            if (pumpLevelEntry->level > 90)
            {
                this->m_newPumpState = PumpState::CLOSED;
            }
            else
            {
                this->m_newPumpState = PumpState::OPEN;
            }
        }
        it = entries.erase(it);
    }
}

bool ControllerApp::step()
{
    LoRa.receive();
    digitalWrite(GPIO_NUM_32, !this->m_newPumpState);
    return true;
}
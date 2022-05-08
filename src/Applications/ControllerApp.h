#pragma once
#include "Application.h"
#include "../Entries/Entries.h"

class ControllerApp : public Application
{
    enum PumpState
    { // OPEN => HIGH, CLOSED => LOW
        OPEN = LOW,
        CLOSED = HIGH
    };

public:
    uint16_t prm_pin_pump;
    unsigned long prm_safety_mode_init_timeout;
    unsigned long prm_safety_mode_pumping_period;
    unsigned long prm_safety_mode_resting_period;
    bool prm_invert;

    bool safety_mode;

    PumpState m_pumpState;
    PumpState m_newPumpState;

public:
    ControllerApp() : Application(), prm_pin_pump(GPIO_NUM_32), prm_safety_mode_init_timeout(60000), prm_safety_mode_pumping_period(60000), prm_safety_mode_resting_period(60 * 60000){};
    ~ControllerApp(){};

public:
    void loadConfig(JsonObject *jsonConfig) override;

    void up(uint8_t *payload, uint8_t length) override;

public:
    bool step() override;
};
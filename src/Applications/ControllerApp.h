#pragma once
#include "Application.h"
#include "../Entries/Entries.h"

class ControllerApp : public Application {
    enum PumpState { // OPEN => HIGH, CLOSED => LOW
        OPEN = LOW,
        CLOSED = HIGH
    };

    public:
        PumpState m_pumpState;
        PumpState m_newPumpState;
    public:
        ControllerApp() : Application() {};
        ~ControllerApp() {};
    public:
        void up(uint8_t* payload, uint8_t length) override;
    public:
        bool run() override;
};
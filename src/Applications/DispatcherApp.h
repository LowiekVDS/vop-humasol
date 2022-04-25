#pragma once
#include "Application.h"

class DispatcherApp : public Application {

    private:
        unsigned long m_lastSent;
    public:
        DispatcherApp() : Application(), m_lastSent(0) {};
        ~DispatcherApp() {};

    public:
        void up(uint8_t* payload, uint8_t length) override {};
    public:
        bool step() override;
    public:
        void runPump();
        void runBattery();
};
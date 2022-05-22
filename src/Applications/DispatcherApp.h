#pragma once
#include "Application.h"

/**
 * The DispatcherApp is the main application for the transmitter, which measures the water tank. 
 * It occasionally sends a message, waits for an ACK and goes back to sleep.
 */

class DispatcherApp : public Application {

    private:
        unsigned long m_lastSent;

    public:
        uint16_t prm_send_interval;
        uint16_t prm_pin_floatswitch;
        bool prm_invert;

        bool configuring;

        DispatcherApp() : Application(), prm_send_interval(4000), prm_pin_floatswitch(26), prm_invert(false), configuring(false) {};
        ~DispatcherApp() {};

    public:

        void loadConfig(JsonObject *jsonConfig) override ;

        void up(uint8_t* payload, uint8_t length) override ;
    public:
        bool step() override;
    public:
        void runLoRaFeedback();
        void runPump();
        void runBattery();
};
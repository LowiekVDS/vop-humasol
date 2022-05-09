#pragma once
#include "../Layers/ApplicationLayer.h"
#include "Application.h"

enum PingPongAppStates {
    IDLE,
    SENT_PING,
    RECEIVED_PONG,
    WAITING,
    TIMEOUT
};

class PingPongApp : public Application {

    private:
        unsigned long timeSent;
        PingPongAppStates state;

        const unsigned long MAX_TIMEOUT = 10000; 

    public:
        PingPongApp() : Application(), timeSent(), state(PingPongAppStates::IDLE) {};
        ~PingPongApp() {};
    
        void up(uint8_t* payload, uint8_t length) override;

        bool step() override;
};
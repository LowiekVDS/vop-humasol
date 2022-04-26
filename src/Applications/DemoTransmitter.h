#pragma once
#include "../Layers/ApplicationLayer.h"
#include "Application.h"

class DemoTransmitterApp : public Application {

    private:
        unsigned long timeSent;

        const unsigned long SEND_INTERVAL = 10000; 

    public:
        DemoTransmitterApp() : Application(), timeSent() {};
        ~DemoTransmitterApp() {};
    
        void up(uint8_t* payload, uint8_t length) override;

        bool step() override;
};
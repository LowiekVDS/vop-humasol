#pragma once
#include "../Layers/ApplicationLayer.h"
#include "Application.h"

class DemoReceiverApp : public Application {

    public:
        DemoReceiverApp() : Application() {};
        ~DemoReceiverApp() {};
    
        void up(uint8_t* payload, uint8_t length) override;

        bool step() override;
};
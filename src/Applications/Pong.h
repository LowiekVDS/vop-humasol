#pragma once
#include "../Layers/ApplicationLayer.h"
#include "Application.h"

class PongApp : public Application {

    public:
        PongApp() : Application() {};
        ~PongApp() {};
    
        void up(uint8_t* payload, uint8_t length) override;
};
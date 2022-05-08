#pragma once
#include "Application.h"

/**
 * The ConfigApp is the main application for the transmitter, which measures the water tank.
 * It occasionally sends a message, waits for an ACK and goes back to sleep.
 */

class ConfigApp : public Application
{

public:
    ConfigApp() : Application(){};
    ~ConfigApp(){};

public:
    void up(uint8_t *payload, uint8_t length) override{};

public:
    void up(uint8_t *payload, uint8_t length) override;

    bool step() override;
};
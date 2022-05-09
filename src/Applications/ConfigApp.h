#pragma once
#include "Application.h"

/**
 * The ConfigApp is the main application for the transmitter, which measures the water tank.
 * It occasionally sends a message, waits for an ACK and goes back to sleep.
 */

enum ConfigStates
{
    CFG_IDLE=0,
    CFG_SENT_CONFIG=1,
    CFG_RECEIVED_CONFIG=2,
    CFG_RECEIVED_PONG=3,
    CFG_SENT_PING=4,
};

class ConfigApp : public Application
{

public:
    ConfigApp() : Application(), state(ConfigStates::CFG_IDLE){};
    ~ConfigApp(){};

    ConfigStates state;

public:
    void up(uint8_t *payload, uint8_t length) override;

    void sendConfig();

    bool step() override;
};
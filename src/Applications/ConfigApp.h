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
    CFG_ERROR=5,
    CFG_LOADED_CONFIG=6,
    CFG_SLAVE_SENT_PING=7, // This can only be used by the slave
    CFG_MASTER_SENT_PONG=8, // Can only be used by the master
    CFG_POSTCONFIG=9
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
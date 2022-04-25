#pragma once
#include "Layer.h"

class TimeoutPacket
{
public:
    unsigned long send_time;
    uint8_t *transport_data;
    uint8_t transport_data_size;

public:
    TimeoutPacket(uint8_t *buffer, uint8_t length, unsigned long send_time);
    ~TimeoutPacket(){};

public:
    void resend(Layer *layer);
};

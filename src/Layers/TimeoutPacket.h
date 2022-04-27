#pragma once
#include "Layer.h"

class TimeoutPacket
{
public:
    unsigned long send_time;
    uint8_t *transport_data;
    uint8_t transport_data_size;
    uint8_t nr_of_resends;

    TimeoutPacket(uint8_t *buffer, uint8_t length, unsigned long send_time);
    ~TimeoutPacket(){};
};

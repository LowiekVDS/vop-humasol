#pragma once
#include "TransportLayer.h"

class TimeoutPacket{
    public:
        unsigned long send_time;
        uint8_t* transport_data;
        uint8_t transport_data_size;

    public:
        TimeoutPacket(uint8_t* buffer, unsigned long send_time) : send_time(send_time),transport_data(buffer){};
    public:
        void resend(TransportLayer* layer);
};

#include "TimeoutPacket.h"
#include "Utils.h"

TimeoutPacket::TimeoutPacket(uint8_t *buffer, uint8_t length, unsigned long send_time)
{
    this->send_time = send_time;
    this->nr_of_resends = 0;
    this->transport_data_size = length;
    this->transport_data = new uint8_t[length];
    memcpy(this->transport_data, buffer, length);
}
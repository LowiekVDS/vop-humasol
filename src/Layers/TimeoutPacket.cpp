#include "TimeoutPacket.h"

TimeoutPacket::TimeoutPacket(uint8_t *buffer, uint8_t length, unsigned long send_time) {
    this->send_time = send_time;
    this->transport_data_size = length;
    this->transport_data = new uint8_t[length];
    memcpy(this->transport_data, buffer, length);
}

void TimeoutPacket::resend(Layer* layer)
{
    printBuffer(this->transport_data, this->transport_data_size);
    layer->down(this->transport_data, transport_data_size);
    delete[] this->transport_data;
}
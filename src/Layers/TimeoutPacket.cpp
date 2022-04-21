#include "TimeoutPacket.h"

void TimeoutPacket::resend(Layer* layer)
{
    layer->down(this->transport_data, transport_data_size);
}
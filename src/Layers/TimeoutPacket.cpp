#include "TimeoutPacket.h"

void TimeoutPacket::resend(TransportLayer* layer)
{
    layer->down(this->transport_data, transport_data_size);
}
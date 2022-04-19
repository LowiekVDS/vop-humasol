#include "TransportLayer.h"

void TransportLayer::up(uint8_t* payload, uint8_t length)
{
    // Parse Header
    TransportLayerHeader header = TransportLayerHeader(payload);
    
    for (auto it = m_sentpackets.begin(); it != m_sentpackets.end(); ++it)
    {
        // If the packet type is DATA, send it up the Layer stack
        if (header.type == TransportLayerHeader::Type::DATA)
        {
            upLayer->up(payload, length-sizeof(TransportLayerHeader));
            sendAck(header.pid);
        } 
        // If the packet type is ACK, remove the packet from the sent packets map
        else if (header.type == TransportLayerHeader::Type::ACK)
        {
            if (it->first == header.pid)
            {
                m_sentpackets.erase(it);
                break;
            }
        }
        
    }
};

void TransportLayer::down(uint8_t* payload, uint8_t length) {
    // Create new buffer
    uint8_t new_length = length + sizeof(TransportLayerHeader);
    uint8_t* new_payload = new uint8_t[new_length];
    uint8_t* pointer = &new_payload[0];

    // Write Transport Header
    TransportLayerHeader header(++m_lastPID, TransportLayerHeader::Type::DATA);
    header.encode(pointer);

    // Add payload
    memcpy(pointer, payload, length);
    
    // Send to down layer
    downLayer->down(new_payload, new_length);
};

bool TransportLayer::step() {
    if (millis()-m_lastTimeoutCheck>TIMEOUT_CHECK_INTERVAL)

    for (auto it = m_sentpackets.begin(); it != m_sentpackets.end(); ++it)
    {
        if (millis() - it->second.send_time > TIMEOUT_LENGTH)
        {
            it->second.resend(this);
        }
    }
}

void TransportLayer::sendAck(uint8_t pid) {
    uint8_t* payload = new uint8_t[sizeof(TransportLayerHeader)];
    uint8_t* pointer = &payload[0];

    TransportLayerHeader header(pid, TransportLayerHeader::Type::ACK);
    header.encode(pointer);

    downLayer->down(payload, sizeof(TransportLayerHeader));
};
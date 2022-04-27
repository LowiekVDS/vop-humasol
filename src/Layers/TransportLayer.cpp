#include "TransportLayer.h"

void TransportLayer::up(uint8_t *payload, uint8_t length)
{
    // Parse Header
    TransportLayerHeader header = TransportLayerHeader(payload);

    if (header.type == TransportLayerHeader::Type::DATA)
    {
        Serial.print("[TRANSPORT]> Received DATA with PID ");
        Serial.println(header.pid);

        for (auto i = 0; i < length; i++)
        {
            Serial.print(payload[i], HEX);
            Serial.print(' ');
        }
        Serial.print(length);
        Serial.println(sizeof(TransportLayerHeader));

        upLayer->up(payload, length - sizeof(TransportLayerHeader));
        sendAck(header.pid);
    }
    else if (header.type == TransportLayerHeader::Type::ACK)
    {
        Serial.print("[TRANSPORT]> Received ACK for package with PID ");
        Serial.println(header.pid);
        for (auto it = m_sentpackets.begin(); it != m_sentpackets.end(); ++it)
        {
            if (it->first == header.pid)
            {
                Serial.println("Erasing the corresponding timeoutpacket");
                m_sentpackets.erase(it);
                break;
            }
        }
    }
    else
    {
        Serial.println("[TRANSPORT]> ERROR: Packet not recognized");
    }

    // for (auto it = m_sentpackets.begin(); it != m_sentpackets.end(); ++it)
    // {
    //     // If the packet type is DATA, send it up the Layer stack
    //     if (header.type == TransportLayerHeader::Type::DATA)
    //     {
    //         upLayer->up(payload, length - sizeof(TransportLayerHeader));
    //         sendAck(header.pid);
    //     }
    //     // If the packet type is ACK, remove the packet from the sent packets map
    // }
};

void TransportLayer::down(uint8_t *payload, uint8_t length)
{
    // Create new buffer
    uint8_t new_length = length + sizeof(uint8_t) + sizeof(uint16_t);
    uint8_t *new_payload = new uint8_t[new_length];
    uint8_t *pointer = &new_payload[0];

    // Write Transport Header
    TransportLayerHeader header(++m_lastPID, TransportLayerHeader::Type::DATA);
    header.encode(pointer);

    // Add payload
    memcpy(pointer, payload, length);
    
    
    // Send to down layer
    downLayer->down(new_payload, new_length);

    Serial.print("[TRANSPORT]> Sending payload with PID ");
    Serial.println(m_lastPID);

    // Add to sentPackets
    m_sentpackets.insert(std::make_pair(m_lastPID, TimeoutPacket(new_payload, new_length, millis())));
};

bool TransportLayer::step()
{
    // if (millis() - m_lastTimeoutCheck > TIMEOUT_CHECK_INTERVAL)

    //     for (auto it = m_sentpackets.begin(); it != m_sentpackets.end(); ++it)
    //     {
    //         if (millis() - it->second.send_time > TIMEOUT_LENGTH)
    //         {
    //             Serial.print("[TRANSPORT]> Resending packet with PID ");
    //             Serial.println(it->first);
    //             it->second.resend(this);
    //             it->second.send_time = millis();
    //         }
    //     }
}

void TransportLayer::sendAck(uint8_t pid)
{
//     uint8_t *payload = new uint8_t[sizeof(TransportLayerHeader)];
//     uint8_t *pointer = &payload[0];

//     TransportLayerHeader header(pid, TransportLayerHeader::Type::ACK);
//     header.encode(pointer);

//     Serial.print("[TRANSPORT]> Sending ACK for PID ");
//     Serial.println(pid);

//     downLayer->down(payload, sizeof(TransportLayerHeader));
// };
};
#include "TransportLayer.h"
#include "Utils.h"

void TransportLayer::up(uint8_t *payload, uint8_t length)
{
    // Parse Header
    TransportLayerHeader header = TransportLayerHeader(payload);

    if (header.type == TransportLayerHeader::Type::DATA)
    {
        Serial.print("[TRANSPORT]> Received DATA with PID ");
        Serial.print(header.pid);
        Serial.print(", and data (incl. 3-byte header): ");
        printBuffer(payload, length);

        upLayer->up(payload + 3, length - 3);
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
                auto correspondingPacket = m_sentpackets.erase(it);
                break;
            }
        }
    }
    else
    {
        Serial.println("[TRANSPORT]> ERROR: Packet not recognized");
    }
};

void TransportLayer::down(uint8_t *payload, uint8_t length)
{
    // Create new buffer
    uint8_t new_length = length + 3; // Our header is 3 bytes long
    uint8_t *new_payload = new uint8_t[new_length];

    // Write Transport Header
    TransportLayerHeader header(++m_lastPID, TransportLayerHeader::Type::DATA);
    header.encode(new_payload);

    // Add payload
    memcpy(new_payload + 3, payload, length);

    // Send to down layer
    Serial.print("[TRANSPORT]> Sending payload with PID ");
    Serial.println(m_lastPID);

    downLayer->down(new_payload, new_length);

    // Add to sentPackets
    m_sentpackets.insert(std::make_pair(m_lastPID, TimeoutPacket(new_payload, new_length, millis())));
};

bool TransportLayer::step()
{
    if (millis() - m_lastTimeoutCheck > TIMEOUT_CHECK_INTERVAL)
    {
        for (auto it = m_sentpackets.begin(); it != m_sentpackets.end(); ++it)
        {
            if (millis() - it->second.send_time > TIMEOUT_LENGTH)
            {

                if (it->second.nr_of_resends > MAX_RETRANSMISSIONS)
                {
                    Serial.print("[TRANSPORT]> Dropping packet with PID ");
                    Serial.print(it->first);
                    Serial.println(", Reason: exceeded MAX_RETRANSMISSIONS");
                    auto correspondingPacket = m_sentpackets.erase(it);
                    break;
                }
                else
                {
                    Serial.print("[TRANSPORT]> Resending packet with PID ");
                    Serial.println(it->first);

                    it->second.nr_of_resends++;
                    this->downLayer->down(it->second.transport_data, it->second.transport_data_size);
                    it->second.send_time = millis();
                }
            }
        }
    }

    return m_sentpackets.size() > 0;
}

void TransportLayer::sendAck(uint8_t pid)
{
    uint8_t *payload = new uint8_t[3]; // Just an ACK, no data. So header size of 3

    TransportLayerHeader header = TransportLayerHeader(pid, TransportLayerHeader::Type::ACK);
    header.encode(payload);

    Serial.print("[TRANSPORT]> Sending ACK for PID ");
    Serial.println(pid);

    downLayer->down(payload, 3);

    delete[] payload;
};
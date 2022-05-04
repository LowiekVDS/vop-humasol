#pragma once
#include "Layer.h"
#include "TimeoutPacket.h"
#include <map>
// #include <vector>
#define TIMEOUT_LENGTH 10000    // in ms; 30 s
#define TIMEOUT_CHECK_INTERVAL 5000 // in ms; 5 s
#define MAX_RETRANSMISSIONS 3

class TransportLayer : public Layer
{
public:
    struct TransportLayerHeader
    {
    public:
        enum Type : uint8_t
        {
            DATA = 0x00,
            ACK = 0x01,
        };

        uint16_t pid;
        Type type;
        TransportLayerHeader(uint8_t pid, Type type = Type::DATA) : pid(pid), type(type){};
        TransportLayerHeader(uint8_t *&buffer) { decode(buffer); };

        void decode(uint8_t *&buffer)
        {
            this->pid = *(uint16_t *)buffer;
            buffer += 2;
            this->type = *(Type *)buffer;
            buffer -= 2;
        };
        void encode(uint8_t *&buffer)
        {
            *(uint16_t *)buffer = this->pid;
            buffer += 2;
            *(Type *)buffer = this->type;
            buffer -= 2;
        };
    };
    std::map<uint16_t, TimeoutPacket> m_sentpackets;
    uint16_t m_lastPID;
    uint16_t m_lastTimeoutCheck;

public:
    TransportLayer() : Layer(), m_lastPID(0), m_lastTimeoutCheck(0){};
    ~TransportLayer(){};

    void up(uint8_t *payload, uint8_t length);
    void down(uint8_t *payload, uint8_t length);

    bool step() override;

private:
    void sendAck(uint8_t pid);
};
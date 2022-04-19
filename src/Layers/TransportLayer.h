#pragma once
#include "Layer.h"
#include "TimeoutPacket.h"
#include <map>
// #include <vector>
#define TIMEOUT_LENGTH 30*1000 // in ms; 30 s
#define TIMEOUT_CHECK_INTERVAL 5000 // in ms; 5 s


class TransportLayer : public Layer
{
    public:
        struct TransportLayerHeader{
            public:
                enum Type : uint8_t{
                    DATA = 0x00, // 0
                    ACK = 0x01, // 8
                };
            public:
                uint16_t pid;
                Type type; // ACK = 0x01, NACK=0x10, NONE=0x00
                TransportLayerHeader(uint8_t pid, Type type = Type::DATA):pid(pid),type(type){};
                TransportLayerHeader(uint8_t*& buffer){ decode(buffer); };
            public:
                void decode(uint8_t*& buffer){
                    this->pid = *(uint16_t*)buffer;
                    buffer+=2;
                    this->type = *(Type*)buffer;
                    buffer++;
                    
                };
                void encode(uint8_t*& buffer){
                    *(uint16_t*)buffer = this->pid;
                    buffer+=2;
                    *(Type*)buffer = this->type;
                    buffer++;
                };
        };
    std::map<uint16_t, TimeoutPacket> m_sentpackets; // (PID, millis)-tuple
    uint16_t m_lastPID;
    uint16_t m_lastTimeoutCheck;
public:
    TransportLayer() : Layer(), m_lastPID(0), m_lastTimeoutCheck(0){};

public:
    void up(uint8_t *payload, uint8_t length);
    void down(uint8_t *payload, uint8_t length);
public:
    bool step() override;
private:
    void sendAck(uint8_t pid);
};
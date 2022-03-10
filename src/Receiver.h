#pragma once

#include <vector>
#include "./Entries/BatteryLevelEntry.h"
#include "./Entries/PumpLevelEntry.h"

#include "./Encryption/EncryptionType.h"

class Receiver {
    private:
        std::vector<TLVEntry*> m_entries;

    public:
        uint8_t* m_buffer;
        uint8_t m_bufferSize;
        EncryptionType m_eType;
    public:
        Receiver(EncryptionType eType = EncryptionType::ENC_AES):m_eType(eType){};
        Receiver(uint8_t* buffer, uint8_t bufferSize, EncryptionType eType = EncryptionType::ENC_AES) : m_buffer(buffer), m_bufferSize(bufferSize), m_eType(eType) {};
        ~Receiver() { delete[] m_buffer;};
    public:
        void parse();
        inline void receive(uint8_t* buffer, uint8_t bufferSize) { m_buffer = buffer; m_bufferSize=bufferSize;};
        void process();
    private:
        void decrypt();
    public:
        inline void setEncryptionType(EncryptionType eType) { this->m_eType = eType; };

};
#pragma once

#include <vector>
#include "Entries/TLVEntry.h"
#include "Constants.h"
#include "./Encryption/EncryptionType.h"

class Sender {
    private:
        std::vector<TLVEntry*> m_entries;
    public:
        uint8_t* m_buffer;
        uint8_t m_bufferSize;
        EncryptionType m_eType;

    public:
        Sender(EncryptionType eType = EncryptionType::ENC_AES) : m_buffer(nullptr), m_bufferSize(0), m_eType(eType) {};
        ~Sender(){ delete[] m_buffer; }
    public:
        void add(TLVEntry* entry);
        uint8_t* send(uint8_t* buffer = nullptr);
    private:
        void encrypt();
    public:
        inline void setEncryptionType(EncryptionType eType) { this->m_eType = eType; };
};
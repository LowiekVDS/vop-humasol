#pragma once

#include <vector>
#include "Entries/TLVEntry.h"
#include "Constants.h"

class Sender {
    private:
        std::vector<TLVEntry*> m_entries;
    public:
        uint8_t* m_buffer;
        uint8_t m_bufferSize;
        bool m_AES = ENCRYPTION;
    public:
        void add(TLVEntry* entry);
        void send();
    private:
        void encrypt();
    public:
        inline void AESenabled(bool enabled) { this->m_AES = enabled; };
};
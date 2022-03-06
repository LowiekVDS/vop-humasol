#pragma once

#include <vector>
#include "./Entries/BatteryLevelEntry.h"
#include "./Entries/PumpLevelEntry.h"

class Receiver {
    private:
        std::vector<TLVEntry*> m_entries;

    public:
        uint8_t* m_buffer;
        uint8_t m_bufferSize;
        bool m_AES = ENCRYPTION;
    public:
        void decrypt();
        void parse();
        void process();
    public:
        inline void AESenabled(bool enabled) { this->m_AES = enabled; };

};
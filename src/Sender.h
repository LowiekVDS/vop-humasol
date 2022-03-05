#pragma once

#include <vector>
#include "Entries/TLVEntry.h"

class Sender {
    private:
        std::vector<TLVEntry*> m_entries;
    public:
        //void add_battery_level(uint8_t);
        //void add_battery_level(uint8_t);
        void add(TLVEntry* entrty);
        void send();
};
#pragma once

#include "Entries/TLVEntry.h"
// #include <LoRa.h>
#include <vector>

class Sender {
    private:
        std::vector<TLVEntry*> entries;
    public:
        void add(TLVEntry *entry);
        void send();
};
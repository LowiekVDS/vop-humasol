#pragma once
#include <stdint.h>

struct TLVEntry {
    public:
        uint8_t type;
    public:
        TLVEntry(uint8_t type) : type(type){};

    virtual int size() = 0;
};
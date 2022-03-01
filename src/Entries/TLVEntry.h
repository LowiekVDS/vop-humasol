#pragma once

#include "Type.h"
#include <stdint.h>

struct TLVEntry {
    private:
        Type type;
        uint8_t length;
    protected:
        TLVEntry(Type type, uint8_t length) : type(type), length(length){};
};
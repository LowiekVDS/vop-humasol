#include "TLVEntry.h"
#include "Type.h"
#include <stdint.h>
struct PumpLevelEntry : public TLVEntry {
    public:
        uint8_t level;
    public:
        PumpLevelEntry(uint8_t level) : TLVEntry(Type::PUMP_LEVEL, 1), level(level){};

};
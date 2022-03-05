#pragma once

#include <vector>
#include "./Entries/BatteryLevelEntry.h"
#include "./Entries/PumpLevelEntry.h"

class Receiver {
    private:
        void (*batteryLevelCallback)(BatteryLevelEntry*);
        void (*pumpLevelCallback)(PumpLevelEntry*);

        std::vector<TLVEntry*> m_entries;

    public:
        void parse(uint8_t* buffer, uint8_t payloadSize);
        void process();

    public:
        void setBatteryLevelCallback(void (*callback)(BatteryLevelEntry*)){ batteryLevelCallback = callback;};
        void setPumpLevelCallback(void (*callback)(PumpLevelEntry*)){ pumpLevelCallback = callback;};
};
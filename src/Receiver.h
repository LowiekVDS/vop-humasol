#pragma once

#include <vector>
#include "./Entries/BatteryLevelEntry.h"
#include "./Entries/PumpLevelEntry.h"

class Receiver {
    private:
        void (*batteryLevelCallback)(BatteryLevelEntry*);
        void (*pumpLevelCallback)(PumpLevelEntry*);
    public:
        void parse(uint8_t* buffer, uint8_t payloadSize);
        void print_results();

    public:
        void setBatteryLevelCallback(void (*callback)(BatteryLevelEntry*)){ batteryLevelCallback = callback;};
        void setPumpLevelCallback(void (*callback)(PumpLevelEntry*)){ pumpLevelCallback = callback;};
};
#include "Receiver.h"
#include <stdint.h>
#include "constants.h"
#include "./Entries/Type.h"
#include "./Entries/Entries.h"

void Receiver::parse(uint8_t* buffer, uint8_t payloadSize) {
    
    uint8_t offset = 0;

    while (offset<payloadSize) {
        uint8_t type = *(uint8_t*)(&buffer[offset]);

        switch (type)
        {
            case BATTERY_LEVEL:
            {
                BatteryLevelEntry* app_data = new BatteryLevelEntry();
                app_data->length=*(uint8_t*)(&buffer[offset+1]);
                app_data->level=*(uint8_t*)(&buffer[offset+2]);
                batteryLevelCallback(app_data);
                offset+=app_data->size();
                break;
            }
            case PUMP_LEVEL:
            {
                PumpLevelEntry* app_data = new PumpLevelEntry(*(PumpLevelEntry*)&buffer[offset]);
                app_data->length=*(uint8_t*)(&buffer[offset+1]);
                app_data->level=*(uint8_t*)(&buffer[offset+2]);
                pumpLevelCallback(app_data);
                offset+=app_data->size();
                break;
            }
            default:
                break;
            
        }
    }

    
}
void Receiver::print_results(){
    
}

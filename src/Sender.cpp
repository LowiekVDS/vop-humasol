#include "constants.h"
#include "Sender.h"
#include "./Entries/Type.h"
#include "./Entries/Entries.h"
#ifndef DEBUG   
#include <LoRa.h>
#else
#include <stdio.h>
#include <string.h>
#include <iostream>
#endif

void Sender::add(TLVEntry *entry){
    m_entries.push_back(entry);
}

void Sender::send(){
    #ifndef DEBUG
    LoRa.beginPacket();
    #endif

    uint8_t buffer[MAX_PACKET_LENGTH] = {0}; // Sets buffer to 0

    auto it = m_entries.begin();
    uint8_t offset = 0;
    while (it != m_entries.end()){
        TLVEntry *entry = *it;
        *(&buffer[offset]) = entry->type;
        offset++;

        switch(entry->type) {
            case BATTERY_LEVEL:
                {BatteryLevelEntry* bat_entry = (BatteryLevelEntry*)entry;

                *(&buffer[offset]) = bat_entry->length;
                offset++;

                *(&buffer[offset]) = bat_entry->level;
                offset++;}

                break;
            case PUMP_LEVEL:
                {PumpLevelEntry* pump_entry = (PumpLevelEntry*)entry;

                *(&buffer[offset]) = pump_entry->length;
                offset++;

                *(&buffer[offset]) = pump_entry->level;
                offset++;}
                break;
        }
        delete entry;
        it = m_entries.erase(it);
    }
    #ifndef DEBUG
    LoRa.write((uint8_t*)buffer, offset);

    LoRa.endPacket();
    #endif
    
    #ifdef DEBUG
    #if 0
    Serial.println("Sent the following packet:");
    for (int i = 0; i < offset; i++){
        Serial.print((unsigned long)buffer[i], HEX);
        Serial.print(' ');
    }
    #else
    std::cout << "Sent the following packet:" << std::endl;
    for (int i = 0; i < offset; i++){
        //std::cout << std::hex << "0x" << (unsigned long)buffer[i] << " ";
        printf ("%02x " ,(unsigned int)buffer[i]);
    }
    std::cout << std::dec << std::endl;
    #endif
    #endif
}
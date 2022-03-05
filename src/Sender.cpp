#include "Constants.h"
#include "Sender.h"
#include "./Entries/Type.h"
#include "./Entries/Entries.h"
#include "./Utils.h"
#if TARGET == ESP32
#include <LoRa.h>
#include <SPI.h>
#else
#include <stdio.h>
#include <string.h>
#include <iostream>
#endif

void Sender::add(TLVEntry *entry){
    m_entries.push_back(entry);
}

void Sender::send(){
    #if TARGET == ESP32
    LoRa.beginPacket();
    #endif

    uint8_t buffer[MAX_PACKET_LENGTH] = {0}; // Sets buffer to 0
    uint8_t* pointer = &buffer[0];
    uint8_t buffer_size = 0;

    auto it = m_entries.begin();

    while (it != m_entries.end()){
        TLVEntry *entry = *it;
        entry->encode(pointer);
        buffer_size += entry->size();
        delete entry;
        it = m_entries.erase(it);
    }
    #if TARGET == ESP32
    LoRa.write((uint8_t*)buffer, (size_t)buffer_size);

    LoRa.endPacket();
    #endif
    
    #if TARGET == GCC
    #if 0
    Serial.println("Sent the following packet:");
    for (int i = 0; i < offset; i++){
        Serial.print((unsigned long)buffer[i], HEX);
        Serial.print(' ');
    }
    #else
    log("Sent the following packet:");
    for (int i = 0; i < buffer_size; i++){
        log("%02x " ,(unsigned int)buffer[i]);
    }
    #endif
    #endif
}
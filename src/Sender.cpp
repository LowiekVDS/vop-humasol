#include "Sender.h"

void Sender::add(TLVEntry *entry){
    entries.push_back(entry);
}

void Sender::send(){
    // Lora.beginPacket();
    auto it = entries.begin();
    while (it != entries.end()){
        TLVEntry *entry = *it;
        // LoRa.write(entries, sizeof(*entry));
        delete entry;
        it = entries.erase(it);
    }

    // LoRa.endPacket();
}
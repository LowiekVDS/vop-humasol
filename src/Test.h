#pragma once

#include "Sender.h"
#include "./Entries/Entries.h"

#include "Receiver.h"
#include <iostream>


int main() {
    uint8_t* buffer;
    uint8_t bufferSize;
    
    std::cout << "=== Sender ===" << std::endl;
    // Sender
    Sender* sender = new Sender(EncryptionType::ENC_AES);
    sender->add(new PumpStateEntry(PUMP_OPEN));

    buffer = sender->send(&bufferSize);
    delete sender;

    std::cout << "=== Receiver ===" << std::endl;
    // Receiver
    Receiver* receiver = new Receiver(buffer, bufferSize, EncryptionType::ENC_AES);
    receiver->parse();
    receiver->process();
    delete receiver;

    return 0;
}
#include "Constants.h"
#include "Sender.h"
#include "./Entries/Type.h"
#include "./Entries/Entries.h"
#include "./Utils.h"
#include "./Encryption/AES.h"
#include <math.h>
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
    m_bufferSize+=entry->size();
}

void Sender::send(){
    if (m_AES)
        m_bufferSize = roundUp(m_bufferSize, 16); // Pad with zeros for AES encryption

    m_buffer = new uint8_t[m_bufferSize] {0}; // Sets buffer to 0;
    uint8_t* pointer = &m_buffer[0];

    auto it = m_entries.begin();

    while (it != m_entries.end()){
        TLVEntry *entry = *it;
        entry->encode(pointer);
        delete entry;
        it = m_entries.erase(it);
    }
    if (m_AES)
        encrypt();

    #if TARGET == ESP32
    LoRa.beginPacket();

    LoRa.write((uint8_t*)m_buffer, (size_t)m_bufferSize);

    LoRa.endPacket();
    #endif

    delete[] m_buffer;
    
    #if TARGET == ESP32
    Serial.println("Sent the following packet:");
    for (int i = 0; i < m_bufferSize; i++){
        Serial.print((unsigned long)m_buffer[i], HEX);
        Serial.print(' ');
    }
    #else
    log("Sent the following packet:");
    for (int i = 0; i < m_bufferSize; i++){
        log("0x%02x, " , m_buffer[i]);
    }
    #endif
}

void Sender::encrypt() {
    uint8_t key[16] = AES_KEY;
    uint8_t init_vector[16] = AES_IV;

    AES aes(AESKeyLength::AES_128);
    uint8_t* cypher_text = aes.EncryptCBC(&m_buffer[0], m_bufferSize, &key[0], &init_vector[0]);

    delete[] m_buffer;
    m_buffer = cypher_text;
}
#pragma once

#include <vector>
#include "./EncryptionLayer.h"
#include "../Encryption/AES.h"
void EncryptionLayer::up(uint8_t *payload, uint8_t length)
{
    payload = decrypt(payload, length);
    
    upLayer->up(payload, length);
}

void EncryptionLayer::down(uint8_t *payload, uint8_t length)
{
    // Doe encryptie
    payload = encrypt(payload, length);

    downLayer->down(payload, length);
}


uint8_t* EncryptionLayer::encrypt(uint8_t* payload, uint8_t& length) {
    if (m_eType == EncryptionType::ENC_AES){
        length = roundUp(length, 16); // Round to the next multiple of 16.

        uint8_t* extended_payload = new uint8_t[length]{0};
        memcpy(&extended_payload[0], &payload[0], length);
        delete[] payload;
        payload = extended_payload;

        uint8_t key[16] = AES_KEY; // TODO: Declare these as const variables (or read from FLASH)
        uint8_t init_vector[16] = AES_IV;

        AES aes(AESKeyLength::AES_128);
        uint8_t* cypher_text = aes.EncryptCBC(payload, length, &key[0], &init_vector[0]);

        delete[] payload;

        payload = cypher_text;        
    }
    return payload;
}


uint8_t* EncryptionLayer::decrypt(uint8_t* payload, uint8_t length) {
    
    if (m_eType == EncryptionType::ENC_AES)
    {
        // TODO: ASSERT that payloadSize % 16 == 0;
        AES aes(AESKeyLength::AES_128);

        uint8_t key[16] = AES_KEY;
        uint8_t init_vector[16] = AES_IV;

        uint8_t *plain_text_buffer = aes.DecryptCBC(payload, length, &key[0], &init_vector[0]);

        delete[] payload;
        payload = plain_text_buffer;
    }
    return payload;
}

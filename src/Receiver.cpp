#include "Receiver.h"
#include <stdint.h>
#include "Constants.h"
#include "./Entries/Type.h"
#include "./Entries/TLVEntry.h"
#include "./Encryption/AES.h"
#include <iostream>

void Receiver::decrypt()
{
    if (m_eType == EncryptionType::ENC_AES)
    {
        // TODO: ASSERT that payloadSize % 16 == 0;
        AES aes(AESKeyLength::AES_128);

        uint8_t key[16] = AES_KEY;
        uint8_t init_vector[16] = AES_IV;

        uint8_t *plain_text_buffer = aes.DecryptCBC(&m_buffer[0], m_bufferSize, &key[0], &init_vector[0]);

        delete[] m_buffer;
        m_buffer = plain_text_buffer;
    }
}

void Receiver::parse()
{

    decrypt();

    uint8_t *pointer = &m_buffer[0];

    while ((pointer - m_buffer) < m_bufferSize)
    {
        if (!isType(*pointer))
            break;

        TLVEntry *e = TLVEntry::CreateFromType(*pointer);
        e->decode(pointer);
        m_entries.push_back(e);

        e->print('\n');
    }
}

void Receiver::process()
{
    for (auto it = m_entries.begin(); it != m_entries.end();)
    {
        TLVEntry *entry = *it;
        entry->process();
        it = m_entries.erase(it);
    }
}
#pragma once

#include <vector>
#include "../Entries/TLVEntry.h"
#include "../Constants.h"
#include "./Layer.h"
#include "../Encryption/EncryptionType.h"

class EncryptionLayer : public Layer
{
public:
    EncryptionLayer(EncryptionType eType) : Layer(), m_eType(eType){};

    void up(uint8_t *payload, uint8_t length) override;
    void down(uint8_t *payload, uint8_t length) override;

private:
    EncryptionType m_eType;

    uint8_t *encrypt(uint8_t *payload, uint8_t &length);
    uint8_t *decrypt(uint8_t *payload, uint8_t length);
};
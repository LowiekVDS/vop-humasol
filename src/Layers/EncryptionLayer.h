#pragma once

#include <vector>
#include "Entries/TLVEntry.h"
#include "Constants.h"
#include "./Layer.h"
#include "./Encryption/EncryptionType.h"

class EncryptionLayer : public virtual Layer
{

public:
    void up(uint8_t *payload) override;
    void down(uint8_t *payload) override;
};
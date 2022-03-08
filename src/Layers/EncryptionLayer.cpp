#pragma once

#include <vector>
#include "Entries/TLVEntry.h"
#include "Constants.h"
#include "./EncryptionLayer.h"

void EncryptionLayer::down(uint8_t *payload)
{
    // Doe encryptie

    this->downLayer->down(payload); // Nieuwe payload !
}

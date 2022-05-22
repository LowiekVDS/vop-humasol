#pragma once
#include "Type.h"
#include <stdint.h>
#include <stdio.h>
#include "TLVEntry.h"
#include "ArduinoJson.h"

struct ErrorEntry : public TLVEntry
{
public:
    uint8_t *payload;

    ErrorEntry(uint8_t *payload = nullptr, uint8_t length = 0) : TLVEntry(TRANSPORTLAYER_E, length), payload(payload) {};
    ~ErrorEntry(){
        delete[] payload;
    };

    void encode(uint8_t *&pointer) override;
    void decode(uint8_t *&pointer) override;

    int size() override { return sizeof(type) + sizeof(length) + length; };

    void print(char end = ' ') override
    {
    }
};
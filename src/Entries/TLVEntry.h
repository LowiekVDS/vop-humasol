#pragma once
#include <stdint.h>
#include "Type.h"
#include "../Utils.h"
#include "ArduinoJson.h"

struct TLVEntry
{
public:
    uint8_t type;
    uint8_t length;

    TLVEntry(uint8_t type, uint8_t length) : type(type), length(length){};
    virtual ~TLVEntry(){};

    virtual void encode(uint8_t *&pointer);
    virtual void decode(uint8_t *&pointer);

    virtual int size() = 0;

    virtual void print(char end = ' ') = 0;

    static TLVEntry *CreateFromType(uint8_t type);
};
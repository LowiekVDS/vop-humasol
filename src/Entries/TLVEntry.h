#pragma once
#include <stdint.h>
#include "Type.h"
#include "../Utils.h"

struct TLVEntry
{
public:
    uint8_t type;
    uint8_t length;

public:
    TLVEntry(uint8_t type, uint8_t length) : type(type), length(length){};
    virtual ~TLVEntry(){};

public:
    virtual void encode(uint8_t *&pointer);
    virtual void decode(uint8_t *&pointer);

    virtual void process() = 0;

    virtual int size() = 0;

    virtual void print(char end = ' ') = 0;
public:
    static TLVEntry* CreateFromType(uint8_t type);


};
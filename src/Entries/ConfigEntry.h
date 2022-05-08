#pragma once

#include <stdint.h>
#include <stdio.h>
#include "TLVEntry.h"
#include "./Type.h"
#include "ArduinoJson.h"

struct ConfigEntry : public TLVEntry
{
public:
    uint8_t type[5];     // Should be 5 characters long
    uint8_t password[16]; // Should be 16 characters long

public:
    ConfigEntry(uint8_t *typePtr = nullptr, uint8_t *passwordPtr = nullptr);
    ~ConfigEntry(){};

public:
    void encode(uint8_t *&pointer) override;
    void decode(uint8_t *&pointer) override;

public:
    int size() override { return sizeof(type) + sizeof(length) + length; };

public:
    void print(char end = ' ') override{};
};
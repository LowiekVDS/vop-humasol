#pragma once
#include "Type.h"
#include <stdint.h>
#include <stdio.h>
#include "TLVEntry.h"
#include "ArduinoJson.h"

#define PUMP_OPEN 0x00
#define PUMP_CLOSE 0xff

struct PumpStateEntry : public TLVEntry{
    public:
        uint8_t state; // PUMP_OPEN or PUMP_CLOSE
    public:
        PumpStateEntry(uint8_t state=0): TLVEntry(PUMP_STATE, 1), state(state){};
        ~PumpStateEntry(){};

    public:
        void encode(uint8_t*& pointer) override;
        void decode(uint8_t*& pointer) override;

    public:
        TLVEntry* process(JsonObject* configuration) override;


    int size() override { return sizeof(type) + sizeof(length) + sizeof(state);};
    
    public:
        void print(char end=' ') override {
            log("Type: %s\nLength: %d\nState: %s\n%c", "PumpStateEntry", (uint8_t)this->length, this->state==PUMP_CLOSE?"PUMP_CLOSE":"PUMP_OPEN", end);
        } 
};
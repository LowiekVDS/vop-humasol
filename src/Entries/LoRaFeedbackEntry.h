#pragma once

#include <stdint.h>
#include <stdio.h>
#include "TLVEntry.h"
#include "./Type.h"
#include "ArduinoJson.h"

struct LoRaFeedbackEntry : public TLVEntry
{
public:
    int RSSI;
    float SNR;

public:
    LoRaFeedbackEntry(int RSSI, float SNR) : TLVEntry(LORA_FEEDBACK, sizeof(float) + sizeof(int)), RSSI(RSSI), SNR(SNR){};
    ~LoRaFeedbackEntry(){};

public:
    void encode(uint8_t *&pointer) override;
    void decode(uint8_t *&pointer) override;

public:
    int size() override { return sizeof(type) + sizeof(length) + length; };

public:
    void print(char end = ' ') override{};
};
#include "LoRaFeedbackEntry.h"
#include "ArduinoJson.h"

void LoRaFeedbackEntry::encode(uint8_t *&pointer)
{
    TLVEntry::encode(pointer);

    *pointer = RSSI;
    pointer += sizeof(int);
    *pointer = SNR;
    pointer += sizeof(float);
}

void LoRaFeedbackEntry::decode(uint8_t *&pointer)
{
    TLVEntry::decode(pointer);

    RSSI = *pointer;
    pointer += sizeof(int);
    SNR = *pointer;
    pointer += sizeof(float);
}
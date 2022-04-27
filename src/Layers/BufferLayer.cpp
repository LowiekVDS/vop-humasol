#include "BufferLayer.h"
#include "Env.h"
#include "Utils.h"

void BufferLayer::up(uint8_t *payload, uint8_t length)
{

    if (this->upBuffer.size() >= MAX_BUFFER_SIZE)
    {
        this->log("UP-BUFFER OVERFLOW", ERROR);
    }
    else
    {

        Payload *payloadStruct = new Payload();
        payloadStruct->length = length;
        payloadStruct->payload = new uint8_t[length];
        memcpy(payloadStruct->payload, payload, length);
        if (DEBUG)
        {
            Serial.print("[BFR ");
            Serial.print(this->id);
            Serial.print("]> Putting something in up-buffer: ");
        }
        printBuffer(payloadStruct->payload, payloadStruct->length);
        this->upBuffer.push(*payloadStruct);
    }

    return;
}

void BufferLayer::down(uint8_t *payload, uint8_t length)
{

    if (this->downBuffer.size() >= MAX_BUFFER_SIZE)
    {
        this->log("DOWN-BUFFER OVERFLOW", ERROR);
    }
    else
    {

        Payload *payloadStruct = new Payload();
        payloadStruct->length = length;
        payloadStruct->payload = new uint8_t[length];
        memcpy(payloadStruct->payload, payload, length);
        if (DEBUG)
        {
            Serial.print("[BFR ");
            Serial.print(this->id);
            Serial.print("]> Putting something in down-buffer: ");
        }
        printBuffer(payloadStruct->payload, payloadStruct->length);
        this->downBuffer.push(*payloadStruct);
    }

    return;
}

boolean BufferLayer::stepUp()
{

    if (this->upBuffer.size() == 0)
        return false;

    if (DEBUG)
    {
        Serial.print("[BFR ");
        Serial.print(this->id);
        Serial.print("]> Sending something up");
    }
    Payload payloadToPushUp = this->upBuffer.front();
    printBuffer(payloadToPushUp.payload, payloadToPushUp.length);
    this->upLayer->up(payloadToPushUp.payload, payloadToPushUp.length);

    delete[] payloadToPushUp.payload;
    delete &payloadToPushUp;

    this->upBuffer.pop();

    return this->upBuffer.size() == 0;
}

boolean BufferLayer::stepDown()
{

    if (this->downBuffer.size() == 0)
        return false;

    if (DEBUG)
    {
        Serial.print("[BFR ");
        Serial.print(this->id);
        Serial.print("]> Sending something down");
    }

    Payload payloadToPushDown = this->downBuffer.front();
    printBuffer(payloadToPushDown.payload, payloadToPushDown.length);
    this->downLayer->down(payloadToPushDown.payload, payloadToPushDown.length);

    delete[] payloadToPushDown.payload;
    delete &payloadToPushDown;

    this->downBuffer.pop();

    return this->downBuffer.size() == 0;
}
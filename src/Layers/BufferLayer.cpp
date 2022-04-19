#include "BufferLayer.h"

void BufferLayer::up(uint8_t *payload, uint8_t length)
{ Serial.println("GOT SOMETHN BUFFER UP");

    if (this->upBuffer.size() >= MAX_BUFFER_SIZE)
    {
        this->log("UP-BUFFER OVERFLOW", ERROR);
    }
    else
    {

        Payload *payloadStruct = new Payload();
        payloadStruct->length = length;
        payloadStruct->payload = payload;

        this->upBuffer.push(*payloadStruct);
    }

    return;
}

void BufferLayer::down(uint8_t *payload, uint8_t length)
{


    Serial.println("GOT SOMETHN BUFFER");
    Serial.println(length);
    if (this->downBuffer.size() >= MAX_BUFFER_SIZE)
    {
        this->log("DOWN-BUFFER OVERFLOW", ERROR);
    }
    else
    {

        Payload *payloadStruct = new Payload();
        payloadStruct->length = length;
        payloadStruct->payload = payload;

        this->downBuffer.push(*payloadStruct);
    }

    return;
}

boolean BufferLayer::stepUp() {

    if (this->upBuffer.size() == 0) return false;

    Payload payloadToPushUp = this->upBuffer.front();
    this->upLayer->up(payloadToPushUp.payload, payloadToPushUp.length);
    this->upBuffer.pop();

    return this->upBuffer.size() == 0;
}

boolean BufferLayer::stepDown() {

    if (this->downBuffer.size() == 0) return false;

    Serial.println("Length");


    Payload payloadToPushDown = this->downBuffer.front();
    Serial.println(payloadToPushDown.length);

    this->downLayer->down(payloadToPushDown.payload, payloadToPushDown.length);

    this->downBuffer.pop();

    return this->downBuffer.size() == 0;
}
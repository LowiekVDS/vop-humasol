#include "PingPong.h"
#include "../Layers/ApplicationLayer.h"
#include "../Entries/Type.h"
#include "../Entries/TLVEntry.h"
#include "Env.h"
#include "../Layers/PhysicalLayer.h"
#include "LoRa.h"

void PingPongApp::up(uint8_t *payload, uint8_t length)
{
    std::vector<TLVEntry *> entries = ApplicationLayer::extractEntries(payload, length);

    for (auto it = entries.begin(); it != entries.end();)
    {
        TLVEntry *entry = *it;

        if (this->state == SENT_PING && entry->type == PONG)
        {
            this->state = RECEIVED_PONG;
        }
        else if (entry->type == PING)
        {
            this->addEntry(TLVEntry::CreateFromType(PONG));
            if (DEBUG)
                Serial.println("[PingPong]> Sending PONG");
        }

        it = entries.erase(it);
    }

    this->flush();
}

bool PingPongApp::step()
{

    switch (this->state)
    {
    case IDLE:
    case TIMEOUT:
    {

        if (DEBUG)
            Serial.println("[PingPong]> Sending PING");

        this->addEntry(TLVEntry::CreateFromType(PING));
        this->state = SENT_PING;
        this->timeSent = millis();
        this->flush();

        return true;
        break;
    }

    case WAITING:
    {
                
        if (millis() - this->timeSent > 1000) {
            this->state = IDLE;
        }
        return false;
        break;
    }
    case RECEIVED_PONG:
    {
        if (DEBUG)
            Serial.println("[PingPong]> PONG received! Pingpong is finishing...");
        this->state = WAITING;
        this->timeSent = millis();

        return false;
        break;
    }
    case SENT_PING:
    {
        LoRa.receive();
        // Check if there is no timeout
        if (millis() - this->timeSent > this->MAX_TIMEOUT)
        {
            this->state = TIMEOUT;
            if (DEBUG)
                Serial.println("[PingPong]> Timeout! Trying again...");
        }

        return false;
        break;
    }

    default:
    {
        return false;
    }
    break;
    }
}
#pragma once
#include "Layer.h"
#include <vector>
#include "Entries/TLVEntry.h"

class ApplicationLayer : public Layer {
    private:
        std::vector<TLVEntry*> m_entries;
        uint8_t m_bufferSize;
    public:
        ApplicationLayer() : Layer() {};
        void up(uint8_t *payload, uint8_t length) override;
        void down(uint8_t *payload, uint8_t length) override;
        void addEntry(TLVEntry* entry);
        void flush();

};
#pragma once
#include "Layer.h"
#include "../Entries/TLVEntry.h"


class ApplicationLayer : public Layer {
    private:
        std::vector<TLVEntry*> m_entries;
    public:
        void up(uint8_t *payload, uint8_t length) override;
        void down(uint8_t *payload, uint8_t length) override;
    private:
        void extractEntries(uint8_t *payload, uint8_t length);
};
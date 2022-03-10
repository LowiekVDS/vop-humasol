#pragma once

#include <vector>
#include "Layer.h"
#include "Layers.h"
#include <vector>

class LayerStack {
    private:
        Layer* m_PhysLayer;
        Layer* m_TranspLayer;
        Layer* m_EncrLayer;
        Layer* m_AppLayer;

        Layer* m_topLayer;
        Layer* m_bottomLayer;
    private:
        std::vector<TLVEntry*> m_entries;
        uint8_t m_bufferSize;
    public:
        LayerStack(): m_bufferSize(0) { setupStack();};
    public:
        void addEntry(TLVEntry* entry);
        void flush();
    private:
        void setupStack();
    public:
        void up(uint8_t* payload);
        void down();
};
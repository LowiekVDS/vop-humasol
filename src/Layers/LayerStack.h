#pragma once

#include <vector>
#include "Layer.h"

class LayerStack {
    private:
        Layer* m_topLayer;
        uint8_t m_stackSize;
    public:
        LayerStack(): m_stackSize(0) {};
        void addLayer(Layer*);
        Layer* getTopLayer() {return this->m_topLayer;};
};
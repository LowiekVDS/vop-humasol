#include "LayerStack.h"
#include "../Constants.h"

void LayerStack::addLayer(Layer* layer) {
    if (this->m_stackSize > 0) {
        this->m_topLayer->setUpLayer(layer);
        layer->setDownLayer(this->m_topLayer);
    } 

    this->m_topLayer = layer;
    this->m_stackSize++;
}
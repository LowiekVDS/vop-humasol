#include "LayerStack.h"
#include "../Constants.h"
#include "ArduinoJson.h"
#include "BufferLayer.h"

void LayerStack::addLayer(Layer *layer)
{
    if (this->m_stackSize > 0)
    {
        this->m_topLayer->setUpLayer(layer);
        layer->setDownLayer(this->m_topLayer);
    }

    this->m_topLayer = layer;
    this->m_stackSize++;
}

void LayerStack::loadConfig(JsonObject *json)
{

    Layer *pointer = this->m_topLayer;

    while (pointer)
    {
        pointer->loadConfig(json);
        pointer = pointer->getDownLayer();
    }
}

bool LayerStack::step() {
    Layer *pointer = this->m_topLayer;

    bool activity = false;
    while (pointer) {
        activity |= pointer->step();
        pointer = pointer->getDownLayer();
    }

    this->activity_counter++;
    return activity || this->activity_counter % this->no_activity_limit;
}
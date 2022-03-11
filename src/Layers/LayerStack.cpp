#include "LayerStack.h"
#include "../Constants.h"
#include "ArduinoJson.h"

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
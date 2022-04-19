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

bool LayerStack::removeLayer() {
    if (this->m_stackSize == 0) return false;

    if (this->m_stackSize == 1) {
        this->m_stackSize--;
        this->m_topLayer = nullptr;
        return true;
    }

    this->m_topLayer = this->m_topLayer->getDownLayer();
    this->m_stackSize--;
    return true;
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
/**
 * @brief 
 *    Layer *pointer = this->m_topLayer;

    bool activity = false;
    while (pointer) {
        activity |= pointer->step();
        pointer = pointer->getDownLayer();
    }

    this->activity_counter++;
    return activity || this->activity_counter % this->no_activity_limit;

 * 
 */
    if (!this->steppingPointer) {
        this->steppingPointer = this->m_topLayer;
    }

    bool activity = this->steppingPointer->step();
    this->steppingPointer = this->steppingPointer->getDownLayer();

    // Serial.println("HAHA");
    // Serial.println(this->activity_counter);
    // Serial.println(this->no_activity_limit);
    // Serial.println(this->activity_counter % this->no_activity_limit);

    return activity || this->activity_counter % this->no_activity_limit == 0;
}
#pragma once

#include <vector>
#include "Layer.h"

/**
 * @brief Stack handler. 
 * 
 * Has some methods to handle the stack
 */
class LayerStack {
    private:
        Layer* m_topLayer;
        uint8_t m_stackSize;
    public:
        LayerStack(): m_stackSize(0) {};

        /**
         * @brief Adds a new layer on top of the stack and connects it correctly to the existing stack
         * 
         * @param Layer* layer : the layer to add
         */
        void addLayer(Layer* layer);

        /**
         * @brief Get the Top Layer object
         * 
         * @return Layer* 
         */
        Layer* getTopLayer() {return this->m_topLayer;};

        void loadConfig(JsonObject *jsonConfig);
};
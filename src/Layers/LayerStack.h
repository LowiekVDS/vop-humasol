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
        const unsigned long no_activity_limit;
        unsigned long activity_counter;
        bool activity;
        Layer* steppingPointer;
    public:
        LayerStack(): m_stackSize(0), no_activity_limit(10000), activity_counter(0), activity(false), steppingPointer(nullptr) {};

        /**
         * @brief Adds a new layer on top of the stack and connects it correctly to the existing stack
         * 
         * @param Layer* layer : the layer to add
         */
        void addLayer(Layer* layer);

        bool removeLayer();

        /**
         * @brief Get the Top Layer object
         * 
         * @return Layer* 
         */
        Layer* getTopLayer() {return this->m_topLayer;};

        void loadConfig(JsonObject *jsonConfig);

        /**
         * Processes the network activity throughout the stack
         * 
         * @returns wether or not the network is still busy
         */
        bool step();
};
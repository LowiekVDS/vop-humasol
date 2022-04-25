#pragma once

#include "Layer.h"
#include <queue>

#define MAX_BUFFER_SIZE 16

struct Payload
{
    uint8_t *payload;
    uint8_t length;
};

class BufferLayer : public Layer
{

private:
    std::queue<Payload> upBuffer;
    std::queue<Payload> downBuffer;
    uint8_t id;

public:
    BufferLayer(uint8_t id) : Layer(), id(id) {}

    /**
     * The up and down methods only put new payload pointers in the buffers.
     * Remember that the up and down methods are called synchronously by other layers.
     *
     * The LayerStack or loop should then also call the step method of the BufferLayers,
     * this way the layerstack can be ran somewhat asynchronously.
     */
    void up(uint8_t *payload, uint8_t length) override;
    void down(uint8_t *payload, uint8_t length) override;

    boolean stepUp();
    boolean stepDown();
    boolean step() override
    {

        boolean resultUp = this->stepUp();
        boolean resultDown = this->stepDown();

        return resultUp || resultDown;
    };
};
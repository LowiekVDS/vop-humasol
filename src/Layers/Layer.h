#pragma once
class Layer
{

protected:
    Layer *upLayer;
    Layer *downLayer;

public:
    Layer(Layer *downLayer) : upLayer(nullptr), downLayer(downLayer){};
    ~Layer() {}

public:
    virtual void up(uint8_t *payload, int8_t length) = 0;
    virtual void down(uint8_t *payload, int8_t length) = 0;

    inline void setUpLayer(Layer *layer) { this->upLayer = layer; };
    inline void setDownLayer(Layer *layer) { this->downLayer = layer; };
};
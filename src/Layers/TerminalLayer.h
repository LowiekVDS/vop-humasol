#pragma once
#include <stdint.h>
#include "ArduinoJson.h"
#include "Layer.h"

enum TerminalLayerType
{
    BOTTOM,
    TOP
};

/**
 * @brief Abstract class to represent a network layer
 */
class TerminalLayer : public Layer
{

private:
    TerminalLayerType type;

public:
    TerminalLayer(TerminalLayerType type) : Layer(), type(type){};

    inline void setDownLayer(Layer *layer)
    {

        if (this->type == BOTTOM)
            throw "ApplicationLayer is bottom terminal. It doesn't support a layer below itself";

        Layer::setDownLayer(layer);
    };

    inline void setUpLayer(Layer *layer)
    {

        if (this->type == TOP)
            throw "ApplicationLayer is top terminal. It doesn't support a layer above itself";

        Layer::setUpLayer(layer);
    };
};

class BottomTerminalLayer : public TerminalLayer
{
public:
    BottomTerminalLayer() : TerminalLayer(BOTTOM){};
};

class TopTerminalLayer : public TerminalLayer
{
public:
    TopTerminalLayer() : TerminalLayer(TOP){};
};
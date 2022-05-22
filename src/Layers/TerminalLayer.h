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
 * @brief Abstract class to represent a terminal network layer
 * 
 * A terminal layer is a layer that only has one neighbouring layer (top or bottom)
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

enum TopLayerActions {
    TLA_SLEEP,
    TLA_IDLE,
    TLA_RESTART,
    TLA_LOAD_CONFIG
};

class TopTerminalLayer : public TerminalLayer
{
public:
    TopLayerActions action;
  
    TopTerminalLayer() : TerminalLayer(TOP), action(TLA_IDLE) {};
    
};
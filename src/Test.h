#pragma once

#include "Sender.h"
#include "./Entries/Entries.h"

#include "Receiver.h"
#include <iostream>

#include "./Layers/LayerStack.h"


int main() {
    LayerStack* layerStack = new LayerStack();

    layerStack->addEntry(new BatteryLevelEntry(25));
    layerStack->addEntry(new PumpStateEntry(25));
    layerStack->flush();

    delete layerStack;
    return 0;
}
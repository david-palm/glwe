#pragma once

#include <vector>

#include "Layer.h"

class LayerStack
{
public:
    LayerStack();
    ~LayerStack();

    void pushLayer(Layer* layer);
    void popLayer(Layer* layer);

    void pushOverlay(Layer* layer);
    void popOverlay(Layer* layer);

    std::vector<Layer*>::iterator begin() { return m_Layers.begin(); };
    std::vector<Layer*>::iterator end() { return m_Layers.end(); };

private:
    std::vector<Layer*> m_Layers;
    std::vector<Layer*>::iterator m_LayerInsert;

};

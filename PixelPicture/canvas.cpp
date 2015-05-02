#include "canvas.h"

Canvas::Canvas(int p)
{
    pixelNumber = p;
    Layer* l = new Layer(p);
    activeLayer = l;
    combinedLayer = new Layer(p);
    layers.append(l);
}

Canvas::~Canvas()
{
    while (!layers.isEmpty())
        delete layers.takeFirst();
}

void Canvas::addLayer(int i)
{
    Layer *l = new Layer(pixelNumber);
    activeLayer = l;
    layers.insert(i,l);
}

void Canvas::switchLayers(int i, int j)
{
    Layer *l = layers[i];
    layers[i] = layers[j];
    layers[j] = l;
}

void Canvas::updateCombined()
{
    for(int index = 0; index < pixelNumber; index++)
        updateCombinedLayer(p->index);
}

void Canvas::updateCombinedLayer(int index)
{
    if(!activeLayer->pixels[index]->clear && !activeLayer->transparent)
    {
        combinedLayer->pixels[index]->clear = false;
        combinedLayer->pixels[index]->color = activeLayer->pixels[p]->color;
    }
    else
    {
        int i = 0;
        while(i<layers.size() && (layers[i]->pixels[index]->clear || layers[i]->transparent))
            i++;
        if(i==layers.size())
        {
            combinedLayer->pixels[index]->clear = true;
        }
        else
        {
            combinedLayer->pixels[index]->clear = false;
            combinedLayer->pixels[index]->color = layers[i]->pixels[index]->color;
        }
    }
}

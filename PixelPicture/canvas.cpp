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

#include "canvas.h"

Canvas::Canvas(int p)
{
    numberofPixels = p;
    Layer* l = new Layer(p);
    activeLayer = l;
    l->setName("Layer0");
    combinedLayer = new Layer(p);
    layers.append(l);
}

Canvas::~Canvas()
{
    while (!layers.isEmpty())
        delete layers.takeFirst();
}

void Canvas::setLayerName(QString s)
{
    activeLayer->setName(s);
}

QString Canvas::getLayerName()
{
    return activeLayer->getName();
}

QString Canvas::getLayerName(int index)
{
    return layers[index]->getName();
}

void Canvas::setLayerTransparency(bool t)
{
    activeLayer->setTransparency(t);
    updateCombined();
}

void Canvas::setActiveLayer(int index)
{
    activeLayer = layers[index];
    updateCombined();
}

void Canvas::setColorofPixel(int index, QColor color)
{
    activeLayer->setColorofPixel(index, color);
    updateCombinedLayer(index);
}

QColor Canvas::getColorofPixel(int index)
{
    return combinedLayer->getColorofPixel(index);
}

bool Canvas::isPixelClear(int index)
{
    return combinedLayer->isPixelClear(index);
}

void Canvas::clearPixel(int index)
{
    activeLayer->clearPixel(index);
    updateCombinedLayer(index);
}

void Canvas::clearLayer()
{
    activeLayer->clear();
    updateCombined();
}

void Canvas::addLayer()
{
    int index = layers.indexOf(activeLayer);
    addLayer(index);
}

void Canvas::removeActiveLayer()
{
    int index = layers.indexOf(activeLayer);
    if(index == 0)
    {
        layers.removeFirst();
        delete activeLayer;
        if(layers.size() == 0)
        {
            addLayer(0);
        }
        else
        {
            activeLayer = layers[0];
        }
    }
    else
    {
        layers.removeAt(index);
        delete activeLayer;
        activeLayer = layers[index-1];
    }
    updateCombined();
}

void Canvas::addLayer(int index)
{
    Layer *l = new Layer(numberofPixels);
    activeLayer = l;
    layers.insert(index,l);
}

void Canvas::switchLayers(int i, int j)
{
    Layer *l = layers[i];
    layers[i] = layers[j];
    layers[j] = l;

    updateCombined();
}

void Canvas::updateCombined()
{
    for(int index = 0; index < numberofPixels; index++)
        updateCombinedLayer(index);
}

void Canvas::updateCombinedLayer(int index)
{
    if(!activeLayer->isPixelClear(index) && !activeLayer->getTransparency())
    {
        combinedLayer->setColorofPixel(index,activeLayer->getColorofPixel(index));
    }
    else
    {
        int i = 0;
        while(i<layers.size() && (layers[i]->isPixelClear(index) || layers[i]->getTransparency()))
            i++;

        if(i==layers.size())
        {
            combinedLayer->clearPixel(index);
        }
        else
        {
            combinedLayer->setColorofPixel(index, layers[i]->getColorofPixel(index));
        }
    }
}

int Canvas::numberofLayers()
{
    return layers.size();
}

bool Canvas::getTransparency(int index)
{
    return layers[index]->getTransparency();
}

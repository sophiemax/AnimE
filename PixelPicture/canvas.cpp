#include "canvas.h"

Canvas::Canvas(int r, int c)
{
    originalnumberofcolumns = r;
    originalnumberofrows = c;
    combinedLayer = new Layer(r,c);
    combinedLayer->initialize();
}

Canvas::Canvas(Canvas *c, int r, int col)
{
    int  numberoflayers = c->numberofLayers();

    originalnumberofcolumns = r;
    originalnumberofrows = col;

    combinedLayer = new Layer(originalnumberofcolumns,originalnumberofrows);
    combinedLayer->initialize();

    for(int i = 0; i < numberoflayers; i++)
    {
        Layer *l = new Layer(c->getLayer(i),r,col);

        layers.append(l);
    }

    activeLayer = layers[c->getActive()];

    updateCombined();
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

void Canvas::setLayerName(int layerindex, QString name)
{
    layers[layerindex]->setName(name);
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

void Canvas::setLayerTransparency(int layerindex, bool t)
{
    layers[layerindex]->setTransparency(t);
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

QColor Canvas::getColorofPixel(int layerindex, int pixelindex)
{
    return layers[layerindex]->getColorofLayerPixel(pixelindex);
}

bool Canvas::isPixelClear(int index)
{
    return combinedLayer->isPixelClear(index);
}

bool Canvas::isPixelClear(int layerindex, int pixelindex)
{
    return layers[layerindex]->isLayerPixelClear(pixelindex);
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

void Canvas::moveLayerUp()
{
    activeLayer->moveUp();
    updateCombined();
}

void Canvas::moveLayerDown()
{
    activeLayer->moveDown();
    updateCombined();
}

void Canvas::moveLayerLeft()
{
    activeLayer->moveLeft();
    updateCombined();
}

void Canvas::moveLayerRight()
{
    activeLayer->moveRight();
    updateCombined();
}

void Canvas::moveFrameUp()
{
    foreach(Layer *l, layers)
        l->moveUp();
    updateCombined();
}

void Canvas::moveFrameDown()
{
    foreach(Layer *l, layers)
        l->moveDown();
    updateCombined();
}

void Canvas::moveFrameLeft()
{
    foreach(Layer *l, layers)
        l->moveLeft();
    updateCombined();
}

void Canvas::moveFrameRight()
{
    foreach(Layer *l, layers)
        l->moveRight();
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
    Layer *l = new Layer(originalnumberofcolumns, originalnumberofrows);
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

Layer *Canvas::getLayer(int index)
{
    return layers[index];
}

int Canvas::getActive()
{
    return layers.indexOf(activeLayer);
}

void Canvas::initialize()
{
    Layer* l = new Layer(originalnumberofcolumns,originalnumberofrows);
    activeLayer = l;
    l->setName("Layer0");
    layers.append(l);
    initializeLayer();
}

void Canvas::initializeLayer()
{
    activeLayer->initialize();
}

void Canvas::clearAll()
{
    foreach(Layer *l, layers)
    {
        l->clearAll();
    }
    while (!layers.isEmpty())
        delete layers.takeFirst();
    delete combinedLayer;
}

void Canvas::setNumberofrows(int layerindex, int number)
{
    layers[layerindex]->setNumberofrows(number);
}

void Canvas::setNumberofcolumns(int layerindex, int number)
{
    layers[layerindex]->setNumberofcolumns(number);
}

void Canvas::addLayerPixels(int layerindex, QString data)
{
    layers[layerindex]->addLayerPixels(data);
}

void Canvas::setDefaultActives()
{
    activeLayer = layers[0];
}

int Canvas::getLayerSize()
{
    return activeLayer->getSize();
}

void Canvas::updateCombined()
{
    for(int index = 0; index < originalnumberofcolumns * originalnumberofrows; index++)
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

int Canvas::getnumberofcolumns(int index)
{
    return layers[index]->getNumberofColumns();
}

int Canvas::getnumberofrows(int index)
{
    return layers[index]->getNumberofRows();
}

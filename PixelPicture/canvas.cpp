#include "canvas.h"

Canvas::Canvas(int r, int c)
{
    pixelsinarow = r;
    pixelsinacolumn = c;
    Layer* l = new Layer(r,c);
    activeLayer = l;
    l->setName("Layer0");
    combinedLayer = new Layer(r,c);
    layers.append(l);
}

Canvas::Canvas(Canvas *c, int r, int col)
{
    int  numberoflayers = c->numberofLayers();

    pixelsinarow = r;
    pixelsinacolumn = col;

    combinedLayer = new Layer(pixelsinarow,pixelsinacolumn);

    for(int i = 0; i < numberoflayers; i++)
    {
        Layer *l = new Layer(c->getLayer(i),r,col);

        layers.append(l);
    }

    activeLayer = layers[0];

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
    Layer *l = new Layer(pixelsinarow, pixelsinacolumn);
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

void Canvas::updateCombined()
{
    for(int index = 0; index < pixelsinarow * pixelsinacolumn; index++)
        updateCombinedLayer(index);
}

void Canvas::updateCombinedLayer(int index)
{
    if(index == 676)
    {
        QTextStream(stdout) << index << endl;
        QTextStream(stdout) << activeLayer->getSize() << endl;
        QTextStream(stdout) << activeLayer->isPixelClear(index) << endl;
        QTextStream(stdout) << activeLayer->getTransparency() << endl;
    }
    if(!activeLayer->isPixelClear(index) && !activeLayer->getTransparency())
    {
        combinedLayer->setColorofPixel(index,activeLayer->getColorofPixel(index));

        if(index == 676)
            QTextStream(stdout) << "Pina1" << endl;
    }
    else
    {
        int i = 0;
        if(index == 676)
            QTextStream(stdout) << "Pina2" << endl;
        while(i<layers.size() && (layers[i]->isPixelClear(index) || layers[i]->getTransparency()))
            i++;

        if(i==layers.size())
        {
            if(index == 676)
                QTextStream(stdout) << "Pina3" << endl;
            combinedLayer->clearPixel(index);
        }
        else
        {
            if(index == 676)
                QTextStream(stdout) << "Pina4" << endl;
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

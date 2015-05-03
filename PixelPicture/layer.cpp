#include "layer.h"

Layer::Layer(int p)
{
    for(int i = 0; i < p; i++)
    {
        LayerPixel* lp = new LayerPixel();
        lp->place = i;
        pixels.append(lp);
    }
}

Layer::~Layer()
{
    while (!pixels.isEmpty())
        delete pixels.takeFirst();
}

QString Layer::getName()
{
    return name;
}

void Layer::setName(QString s)
{
    name = s;
}

void Layer::setColorofPixel(int index, QColor color)
{
    pixels[index]->clear = false;
    pixels[index]->color = color;
}

QColor Layer::getColorofPixel(int index)
{
    return pixels[index]->color;
}

void Layer::setTransparency(bool t)
{
    transparent = t;
}

bool Layer::getTransparency()
{
    return transparent;
}

bool Layer::isPixelClear(int index)
{
    return pixels[index]->clear;
}

void Layer::clearPixel(int index)
{
    pixels[index]->clear = true;
}

void Layer::clear()
{
    foreach(LayerPixel *lp, pixels)
    {
        lp->clear = true;
    }
}

#include "frame.h"

Frame::Frame(int p)
{
    canvas = new Canvas(p);
}

Frame::~Frame()
{

}

void Frame::setLayerName(QString s)
{
    canvas->setLayerName(s);
}

QString Frame::getLayerName()
{
    return canvas->getLayerName();
}

QString Frame::getLayerName(int index)
{
    return canvas->getLayerName(index);
}

void Frame::setLayerTransparency(bool t)
{
    canvas->setLayerTransparency(t);
}

void Frame::setActiveLayer(int index)
{
    canvas->setActiveLayer(index);
}

void Frame::addLayer()
{
    canvas->addLayer();
}

void Frame::removeActiveLayer()
{
    canvas->removeActiveLayer();
}

void Frame::switchLayers(int i, int j)
{
    canvas->switchLayers(i,j);
}

int Frame::numberofLayers()
{
    return canvas->numberofLayers();
}

void Frame::setColorofPixel(int index, QColor color)
{
    canvas->setColorofPixel(index, color);
}

QColor Frame::getColorofPixel(int index)
{
    return canvas->getColorofPixel(index);
}

bool Frame::isPixelClear(int index)
{
    return canvas->isPixelClear(index);
}

void Frame::clearPixel(int index)
{
    canvas->clearPixel(index);
}

void Frame::clearLayer()
{
    canvas->clearLayer();
}

bool Frame::getTransparency(int index)
{
    return canvas->getTransparency(index);
}

float Frame::getTimespan()
{
    return timespan;
}

void Frame::setTimespan(float t)
{
    timespan = t;
}

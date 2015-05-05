#include "frame.h"

Frame::Frame(int r, int c)
{
    pixelsinarow = r;
    pixelsinacolumn = c;
    name = "Frame";
}

Frame::Frame(Frame *f, int r, int c)
{
    canvas = new Canvas(f->getCanvas(), r, c);
}

Frame::~Frame()
{

}

void Frame::setLayerName(QString s)
{
    canvas->setLayerName(s);
}

void Frame::setLayerName(int layerindex, QString name)
{
    canvas->setLayerName(layerindex, name);
}

QString Frame::getLayerName()
{
    return canvas->getLayerName();
}

QString Frame::getLayerName(int index)
{
    return canvas->getLayerName(index);
}

void Frame::setName(QString s)
{
    name = s;
}

QString Frame::getName()
{
    return name;
}

void Frame::setLayerTransparency(bool t)
{
    canvas->setLayerTransparency(t);
}

void Frame::setLayerTransparency(int layerindex, bool t)
{
    canvas->setLayerTransparency(layerindex, t);
}

void Frame::setActiveLayer(int index)
{
    canvas->setActiveLayer(index);
}

void Frame::addLayer()
{
    canvas->addLayer();
}

void Frame::addLayer(int index)
{
    canvas->addLayer(index);
}

void Frame::addCanvas()
{
    QTextStream(stdout) << pixelsinarow << ";" << pixelsinacolumn << endl;
    canvas = new Canvas(pixelsinarow,pixelsinacolumn);
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

QColor Frame::getColorofPixel(int layerindex, int pixelindex)
{
    return canvas->getColorofPixel(layerindex, pixelindex);
}

bool Frame::isPixelClear(int index)
{
    return canvas->isPixelClear(index);
}

bool Frame::isPixelClear(int layerindex, int pixelindex)
{
    return canvas->isPixelClear(layerindex,pixelindex);
}

void Frame::clearPixel(int index)
{
    canvas->clearPixel(index);
}

void Frame::clearLayer()
{
    canvas->clearLayer();
}

void Frame::moveLayerUp()
{
    canvas->moveLayerUp();
}

void Frame::moveLayerDown()
{
    canvas->moveLayerDown();
}

void Frame::moveLayerLeft()
{
    canvas->moveLayerLeft();
}

void Frame::moveLayerRight()
{
    canvas->moveLayerRight();
}

void Frame::moveFrameUp()
{
    canvas->moveFrameUp();
}

void Frame::moveFrameDown()
{
    canvas->moveFrameDown();
}

void Frame::moveFrameLeft()
{
    canvas->moveFrameLeft();
}

void Frame::moveFrameRight()
{
    canvas->moveFrameRight();
}

bool Frame::getTransparency(int index)
{
    return canvas->getTransparency(index);
}

int Frame::getnumberofcolumns(int index)
{
    return canvas->getnumberofcolumns(index);
}

int Frame::getnumberofrows(int index)
{
    return canvas->getnumberofrows(index);
}

float Frame::getTimespan()
{
    return timespan;
}

void Frame::setTimespan(float t)
{
    timespan = t;
}

Canvas *Frame::getCanvas()
{
    return canvas;
}

void Frame::initialize()
{
    canvas = new Canvas(pixelsinarow,pixelsinacolumn);
    initializeCanvas();
}

void Frame::initializeCanvas()
{
    canvas->initialize();
}

void Frame::initializeLayer()
{
    canvas->initializeLayer();
}

void Frame::clearAll()
{
    canvas->clearAll();
    delete canvas;
}

void Frame::setNumberofrows(int layerindex, int number)
{
    canvas->setNumberofrows(layerindex,number);
}

void Frame::setNumberofcolumns(int layerindex, int number)
{
    canvas->setNumberofcolumns(layerindex,number);
}

void Frame::addLayerPixels(int layerindex, QString data)
{
    canvas->addLayerPixels(layerindex, data);
}

void Frame::updateCombinedLayers()
{
    canvas->updateCombined();
}

void Frame::setDefaultActives()
{
    canvas->setDefaultActives();
}

int Frame::getLayerSize()
{
    return canvas->getLayerSize();
}

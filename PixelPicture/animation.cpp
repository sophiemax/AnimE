#include "animation.h"

Animation::Animation(int r, int c)
{
    pixelsinarow = r;
    pixelsinacolumn = c;

    name = "Animation0";
}

Animation::~Animation()
{
    while (!frames.isEmpty())
        delete frames.takeFirst();
}

void Animation::setLayerName(QString s)
{
    activeFrame->setLayerName(s);
}

void Animation::setLayerName(int frameindex, int layerindex, QString name)
{
    frames[frameindex]->setLayerName(layerindex, name);
}

QString Animation::getLayerName()
{
    return activeFrame->getLayerName();
}

QString Animation::getLayerName(int index)
{
    return activeFrame->getLayerName(index);
}

QString Animation::getLayerName(int frameindex, int layerindex)
{
    return frames[frameindex]->getLayerName(layerindex);
}

void Animation::setFrameName(QString s)
{
    activeFrame->setName(s);
}

void Animation::setFrameName(int index, QString s)
{
    frames[index]->setName(s);
}

QString Animation::getFrameName()
{
    return activeFrame->getName();
}

QString Animation::getFrameName(int index)
{
    return frames[index]->getName();
}

void Animation::setName(QString s)
{
    name = s;
}

QString Animation::getName()
{
    return name;
}

void Animation::setLayerTransparency(bool t)
{
    activeFrame->setLayerTransparency(t);
}

void Animation::setLayerTransparency(int frameindex, int layerindex, bool t)
{
    frames[frameindex]->setLayerTransparency(layerindex, t);
}

void Animation::setActiveLayer(int index)
{
    activeFrame->setActiveLayer(index);
}

int Animation::numberofFrames()
{
    return frames.size();
}

int Animation::numberofLayers()
{
    return activeFrame->numberofLayers();
}

int Animation::numberofLayers(int index)
{
    return frames[index]->numberofLayers();
}

int Animation::getnumberofrows(int frameindex, int layerindex)
{
    return frames[frameindex]->getnumberofrows(layerindex);
}

int Animation::getnumberofcolumns(int frameindex, int layerindex)
{
    return frames[frameindex]->getnumberofcolumns(layerindex);
}

void Animation::setActiveFrame(int index)
{
    activeFrame = frames[index];
}

void Animation::setNextFrameActive()
{
    int index = frames.indexOf(activeFrame);
    if(index != frames.size()-1)
        activeFrame = frames[index + 1];
}

float Animation::getCurrentTimespan()
{
    return activeFrame->getTimespan();
}

void Animation::setTimesum(float t)
{
    timesum = t;
}

void Animation::setTimespan(int index, float t)
{
    frames[index]->setTimespan(t);
}

float Animation::getTimesum()
{
    return timesum;
}

float Animation::getTimespan(int index)
{
    return frames[index]->getTimespan();
}

float Animation::getCurrentTime()
{
    float time = 0.0;
    int index = frames.indexOf(activeFrame);

    for(int i = 0; i <= index; i++)
    {
        time += frames[i]->getTimespan();
    }

    return time;
}

int Animation::getActiveFrameIndex()
{
    return frames.indexOf(activeFrame);
}

bool Animation::getTransparency(int index)
{
    return activeFrame->getTransparency(index);
}

bool Animation::getTransparency(int frameindex, int layerindex)
{
    return frames[frameindex]->getTransparency(layerindex);
}

void Animation::addLayer()
{
    activeFrame->addLayer();
}

void Animation::addLayer(int frameindex, int layerindex)
{
    frames[frameindex]->addLayer(layerindex);
}

void Animation::removeActiveLayer()
{
    activeFrame->removeActiveLayer();
}

void Animation::switchLayers(int i, int j)
{
    activeFrame->switchLayers(i,j);
}

void Animation::addCanvas(int index)
{
    frames[index]->addCanvas();
}

void Animation::addFrame()
{
    int index = frames.indexOf(activeFrame);

    Frame* f = new Frame(pixelsinarow,pixelsinacolumn);

    frames.insert(index + 1, f);
    activeFrame = f;

    timesum += f->getTimespan();
}

void Animation::addFrame(int t)
{
    int index = frames.indexOf(activeFrame);

    Frame* f = new Frame(pixelsinarow, pixelsinacolumn);
    f->setTimespan(t);

    frames.insert(index + 1, f);
    activeFrame = f;

    timesum += t;
}

void Animation::addFrameIndexed(int index)
{
    Frame* f = new Frame(pixelsinarow, pixelsinacolumn);
    frames.insert(index,f);
}

void Animation::copyFrame()
{
    int index = frames.indexOf(activeFrame);

    Frame *f = new Frame(activeFrame, pixelsinarow, pixelsinacolumn);

    frames.insert(index+1,f);
    timesum += f->getTimespan();

    activeFrame = f;
}

void Animation::moveLayerUp()
{
    activeFrame->moveLayerUp();
}

void Animation::moveLayerDown()
{
    activeFrame->moveLayerDown();
}

void Animation::moveLayerLeft()
{
    activeFrame->moveLayerLeft();
}

void Animation::moveLayerRight()
{
    activeFrame->moveLayerRight();
}

void Animation::moveFrameUp()
{
    activeFrame->moveFrameUp();
}

void Animation::moveFrameDown()
{
    activeFrame->moveFrameDown();
}

void Animation::moveFrameLeft()
{
    activeFrame->moveFrameLeft();
}

void Animation::moveFrameRight()
{
    activeFrame->moveFrameRight();
}

void Animation::setColorofPixel(int index, QColor color)
{
    activeFrame->setColorofPixel(index, color);
}

QColor Animation::getColorofPixel(int index)
{
    return activeFrame->getColorofPixel(index);
}

QColor Animation::getColorofPixel(int frameindex, int layerindex, int pixelindex)
{
    return frames[frameindex]->getColorofPixel(layerindex,pixelindex);
}

bool Animation::isPixelClear(int index)
{
    return activeFrame->isPixelClear(index);
}

bool Animation::isPixelClear(int frameindex, int layerindex, int pixelindex)
{
    return frames[frameindex]->isPixelClear(layerindex,pixelindex);
}

void Animation::clearPixel(int index)
{
    activeFrame->clearPixel(index);
}

void Animation::clearLayer()
{
    activeFrame->clearLayer();
}

void Animation::initialize()
{
    Frame* f = new Frame(pixelsinarow,pixelsinacolumn);
    frames.append(f);
    timesum += f->getTimespan();
    activeFrame = f;
    initializeFrame();
}

void Animation::initializeFrame()
{
    activeFrame->initialize();
}

void Animation::initializeCanvas()
{
    activeFrame->initializeCanvas();
}

void Animation::initializeLayer()
{
    activeFrame->initializeLayer();
}

void Animation::clearAll()
{
    foreach(Frame *f, frames)
    {
        f->clearAll();
    }
    while (!frames.isEmpty())
        delete frames.takeFirst();
}

void Animation::setNumberofrows(int frameindex, int layerindex, int number)
{
    frames[frameindex]->setNumberofrows(layerindex,number);
}

void Animation::setNumberofcolumns(int frameindex, int layerindex, int number)
{
    frames[frameindex]->setNumberofcolumns(layerindex, number);
}

void Animation::addLayerPixels(int frameindex, int layerindex, QString data)
{
    frames[frameindex]->addLayerPixels(layerindex, data);
}

void Animation::updateCombinedLayers()
{
    foreach(Frame *f, frames)
        f->updateCombinedLayers();
}

void Animation::setDefaultActives()
{
    activeFrame = frames[0];
    foreach(Frame *f, frames)
        f->setDefaultActives();
}

int Animation::getLayerSize()
{
    return activeFrame->getLayerSize();
}


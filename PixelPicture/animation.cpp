#include "animation.h"

Animation::Animation(int r, int c)
{
    Frame* f = new Frame(r,c);
    pixelsinarow = r;
    pixelsinacolumn = c;
    frames.append(f);
    timesum += f->getTimespan();
    activeFrame = f;
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

QString Animation::getLayerName()
{
    return activeFrame->getLayerName();
}

QString Animation::getLayerName(int index)
{
    return activeFrame->getLayerName(index);
}

void Animation::setLayerTransparency(bool t)
{
    activeFrame->setLayerTransparency(t);
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

void Animation::addLayer()
{
    activeFrame->addLayer();
}

void Animation::removeActiveLayer()
{
    activeFrame->removeActiveLayer();
}

void Animation::switchLayers(int i, int j)
{
    activeFrame->switchLayers(i,j);
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

void Animation::setColorofPixel(int index, QColor color)
{
    activeFrame->setColorofPixel(index, color);
}

QColor Animation::getColorofPixel(int index)
{
    return activeFrame->getColorofPixel(index);
}

bool Animation::isPixelClear(int index)
{
    return activeFrame->isPixelClear(index);
}

void Animation::clearPixel(int index)
{
    activeFrame->clearPixel(index);
}

void Animation::clearLayer()
{
    activeFrame->clearLayer();
}


#include "controller.h"

Controller::Controller(PixelScene *s)
{
    scene = s;

    primaryColor = Qt::white;
    secondaryColor = Qt::black;

    activeAnimation = new Animation(pixelsinaRow(), pixelsinaColumn());
    activeAnimation->initialize();
    animations.append(activeAnimation);

    imageconverter = new ImageConverterTool(this,getPixelSize(), pixelsinaRow(), pixelsinaColumn());
    videoconverter = new VideoConverterTool(this);
}

Controller::~Controller()
{
    delete imageconverter;
    delete videoconverter;

    while (!animations.isEmpty())
        delete animations.takeFirst();
}

int Controller::pixelsinaRow()
{
    return scene->pixelsinaRow();
}

int Controller::pixelsinaColumn()
{
    return scene->pixelsinaColumn();
}

int Controller::numberofPixels()
{
    return scene->numberofPixels();
}

int Controller::getWidth()
{
    return scene->getWidth();
}

int Controller::getOnlyPixelsWidth()
{
    return scene->getOnlyPixelsWidth();
}

int Controller::getHeight()
{
    return scene->getHeight();
}

int Controller::getOnlyPixelsHeight()
{
    return scene->getOnlyPixelsHeight();
}

int Controller::numberofAnimations()
{
    return animations.size();
}

int Controller::numberofFrames()
{
    return activeAnimation->numberofFrames();
}

int Controller::numberofFrames(int index)
{
    return animations[index]->numberofFrames();
}

int Controller::numberofLayers()
{
    return activeAnimation->numberofLayers();
}

int Controller::numberofLayers(int animationindex, int frameindex)
{
    return animations[animationindex]->numberofLayers(frameindex);
}

int Controller::getnumberofrows(int animationindex, int frameindex, int layerindex)
{
    return animations[animationindex]->getnumberofrows(frameindex, layerindex);
}

int Controller::getnumberofcolumns(int animationindex, int frameindex, int layerindex)
{
    return animations[animationindex]->getnumberofcolumns(frameindex, layerindex);
}

void Controller::setActiveFrame(int index)
{
    activeAnimation->setActiveFrame(index);
    updateScene();
}

void Controller::setNextFrameActive()
{
    activeAnimation->setNextFrameActive();
    updateScene();
}

void Controller::setActiveLayer(int index)
{
    activeAnimation->setActiveLayer(index);
    updateScene();
}

bool Controller::getTransparency(int index)
{
    return activeAnimation->getTransparency(index);
}

bool Controller::getTransparency(int animationindex, int frameindex, int layerindex)
{
    return animations[animationindex]->getTransparency(frameindex,layerindex);
}

float Controller::getCurrentTimespan()
{
    return activeAnimation->getCurrentTimespan();
}

float Controller::getTimesum()
{
    return activeAnimation->getTimesum();
}

float Controller::getTimesum(int index)
{
    return animations[index]->getTimesum();
}

float Controller::getTimespan(int index)
{
    return activeAnimation->getTimespan(index);
}

float Controller::getTimespan(int animationindex, int frameindex)
{
    return animations[animationindex]->getTimespan(frameindex);
}

float Controller::getCurrentTime()
{
    return activeAnimation->getCurrentTime();
}

int Controller::getActiveFrameIndex()
{
    return activeAnimation->getActiveFrameIndex();
}

ImageConverterTool *Controller::getImageConverter()
{
    return imageconverter;
}

void Controller::setLayerName(QString s)
{
    activeAnimation->setLayerName(s);
}

QString Controller::getLayerName()
{
    return activeAnimation->getLayerName();
}

QString Controller::getLayerName(int index)
{
    return activeAnimation->getLayerName(index);
}

QString Controller::getLayerName(int animationindex, int frameindex, int layerindex)
{
    return animations[animationindex]->getLayerName(frameindex, layerindex);
}

void Controller::setFrameName(QString s)
{
    activeAnimation->setFrameName(s);
}

QString Controller::getFrameName()
{
    return activeAnimation->getFrameName();
}

QString Controller::getFrameName(int index)
{
    return activeAnimation->getFrameName(index);
}

QString Controller::getFrameName(int animationindex, int frameindex)
{
    return animations[animationindex]->getFrameName(frameindex);
}

QString Controller::getAnimationName(int index)
{
    return animations[index]->getName();
}

void Controller::setLayerTransparency(bool t)
{
    activeAnimation->setLayerTransparency(t);
    updateScene();
}

void Controller::addLayer()
{
    activeAnimation->addLayer();
    activeAnimation->initializeLayer();
}

void Controller::removeActiveLayer()
{
    activeAnimation->removeActiveLayer();
    updateScene();
}

void Controller::switchLayers(int i, int j)
{
    activeAnimation->switchLayers(i,j);
    updateScene();
}

void Controller::addFrame()
{
    activeAnimation->addFrame();
    activeAnimation->initializeFrame();
    updateScene();
}

void Controller::addFrame(int timespan)
{
    activeAnimation->addFrame(timespan);
    activeAnimation->initializeFrame();
    updateScene();
}

void Controller::copyFrame()
{
    activeAnimation->copyFrame();
    updateScene();
}

void Controller::moveLayerDown()
{
    activeAnimation->moveLayerDown();
    updateScene();
}

void Controller::moveLayerLeft()
{
    activeAnimation->moveLayerLeft();
    updateScene();
}

void Controller::moveLayerRight()
{
    activeAnimation->moveLayerRight();
    updateScene();
}

void Controller::moveLayerUp()
{
    activeAnimation->moveLayerUp();
    updateScene();
}

void Controller::moveFrameUp()
{
    activeAnimation->moveFrameUp();
    updateScene();
}

void Controller::moveFrameDown()
{
    activeAnimation->moveFrameDown();
    updateScene();
}

void Controller::moveFrameLeft()
{
    activeAnimation->moveFrameLeft();
    updateScene();
}

void Controller::moveFrameRight()
{
    activeAnimation->moveFrameRight();
    updateScene();
}

void Controller::setColorofPixel(int index)
{
    if(scene->getWindowToggled())
    {
        QList<int> indexes = scene->windowIndexes(index);
        foreach(int i, indexes)
        {
            activeAnimation->setColorofPixel(i, primaryColor);
            scene->updatePixel(i,false,primaryColor);
        }
    }
    else
    {
        activeAnimation->setColorofPixel(index, primaryColor);
        scene->updatePixel(index,false,primaryColor);
    }
}

void Controller::setColorofPixel(int index, QColor color)
{
    if(scene->getWindowToggled())
    {
        QList<int> indexes = scene->windowIndexes(index);
        foreach(int i, indexes)
        {
            activeAnimation->setColorofPixel(i, color);
            scene->updatePixel(i,false,color);
        }
    }
    else
    {
        activeAnimation->setColorofPixel(index, color);
        scene->updatePixel(index,false,color);
    }
}

void Controller::setColorofPixelFill(int index)
{
    activeAnimation->setColorofPixel(index, primaryColor);
    scene->updatePixel(index,false,primaryColor);
}

QColor Controller::getColorofPixel(int index)
{
    return scene->getColorofPixel(index);
}

QColor Controller::getColorofPixel(int animationindex, int frameindex, int layerindex, int pixelindex)
{
    return animations[animationindex]->getColorofPixel(frameindex,layerindex,pixelindex);
}

void Controller::setPrimaryColor(QColor color)
{
    primaryColor = color;
}

QColor Controller::getPrimaryColor()
{
    return primaryColor;
}

void Controller::setSecondaryColor(QColor color)
{
    secondaryColor = color;
}

QColor Controller::getSecondaryColor()
{
    return secondaryColor;
}

void Controller::setActiveTool(Tool *tool)
{
    scene->setActiveTool(tool);
}

void Controller::setWindowToggled(bool toggled)
{
    scene->setWindowToggled(toggled);
}

bool Controller::isPixelClear(int animationindex, int frameindex, int layerindex, int pixelindex)
{
    return animations[animationindex]->isPixelClear(frameindex,layerindex,pixelindex);
}

QColor Controller::getColorofCombinedLayerPixel(int index)
{
    return activeAnimation->getColorofPixel(index);
}

bool Controller::isCombinedLayerPixelClear(int index)
{
    return activeAnimation->isPixelClear(index);
}

void Controller::clearPixel(int index)
{
    if(scene->getWindowToggled())
    {
        QList<int> indexes = scene->windowIndexes(index);
        foreach(int i, indexes)
        {
            activeAnimation->clearPixel(i);
            scene->updatePixel(i,true,Qt::black);
        }
    }
    else
    {
        activeAnimation->clearPixel(index);
        scene->updatePixel(index, true, Qt::black);
    }
}

void Controller::clearLayer()
{
    activeAnimation->clearLayer();
    updateScene();
}

void Controller::importImage(QImage image)
{
    imageconverter->convertImage(image);
}

void Controller::importVideo(QString fileName)
{
    videoconverter->reset();
    videoconverter->setMedia(QUrl::fromLocalFile(fileName));
    videoconverter->start();
}

int Controller::pixelUnderMouse()
{
    return scene->pixelUnderMouse();
}

int Controller::containsPoint(float x, float y)
{
    return scene->containsPoint(x,y);
}

int Controller::nearestPixel(float x, float y)
{
    return scene->nearestPixel(x,y);
}

QRect Controller::nearestPixelRect(float x, float y)
{
    return scene->nearestPixelRect(x,y);
}

QRect Controller::getPixelRect(int index)
{
    return scene->getPixelRect(index);
}

int Controller::getPixelSize()
{
    return scene->getPixelSize();
}

void Controller::updateScene()
{
    for(int index = 0; index < numberofPixels(); index++)
    {
        scene->updatePixel(index, isCombinedLayerPixelClear(index),getColorofCombinedLayerPixel(index));
    }
}

void Controller::addAnimation()
{
    Animation *a = new Animation(pixelsinaColumn(),pixelsinaRow());
    a->initialize();
    animations.append(a);
}

void Controller::addAnimation(int index)
{
    Animation *a = new Animation(pixelsinaColumn(),pixelsinaRow());
    animations.insert(index,a);
}

void Controller::clearAll()
{
    foreach(Animation* a, animations)
    {
        a->clearAll();
        delete a;
    }
}


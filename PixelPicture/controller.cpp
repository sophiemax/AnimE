#include "controller.h"

Controller::Controller(PixelScene *s)
{
    scene = s;

    primaryColor = Qt::white;
    secondaryColor = Qt::black;

    activeAnimation = new Animation(originalnumberofcolumns(), originalnumberofrows());
    activeAnimation->initialize();
    animations.append(activeAnimation);

    imageconverter = new ImageConverterTool(this,getPixelSize(), originalnumberofcolumns(), originalnumberofrows());
    videoconverter = new VideoConverterTool(this);

    exporter = new ExportTool(this);
    importer = new ImportTool(this);

    playTool = new PlayTool(this);

    nameList << "originalnumberofrows" << "originalnumberofcolumns"; //0,1
    nameList << "animation" << "timesum" << "animationname"; //2,3,4
    nameList << "frame" << "timespan" << "framename"; //5,6,7
    nameList << "canvas"; //8
    nameList << "layer" << "numberofrows" << "numberofcolumns" << "transparent" << "layername" << "data"; //9,10,11,12,13,14
}

Controller::~Controller()
{
    delete imageconverter;
    delete videoconverter;

    delete importer;
    delete exporter;

    while (!animations.isEmpty())
        delete animations.takeFirst();
}

int Controller::originalnumberofcolumns()
{
    return scene->originalnumberofcolumns();
}

int Controller::originalnumberofrows()
{
    return scene->originalnumberofrows();
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

void Controller::setTimesum(int index, float t)
{
    animations[index]->setTimesum(t);
}

float Controller::getTimesum()
{
    return activeAnimation->getTimesum();
}

float Controller::getTimesum(int index)
{
    return animations[index]->getTimesum();
}

void Controller::setTimespan(int animationindex, int frameindex, float t)
{
    animations[animationindex]->setTimespan(frameindex, t);
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

void Controller::setLayerName(int animationindex, int frameindex, int layerindex, QString name)
{
    animations[animationindex]->setLayerName(frameindex, layerindex, name);
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

void Controller::setFrameName(int animationindex, int frameindex, QString name)
{
    animations[animationindex]->setFrameName(frameindex,name);
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

void Controller::setAnimationName(int index, QString s)
{
    animations[index]->setName(s);
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

void Controller::setLayerTransparency(int animationindex, int frameindex, int layerindex, bool t)
{
    animations[animationindex]->setLayerTransparency(frameindex, layerindex, t);
}

void Controller::addLayer()
{
    activeAnimation->addLayer();
    activeAnimation->initializeLayer();
}

void Controller::addLayer(int animationindex, int frameindex, int layerindex)
{
    animations[animationindex]->addLayer(frameindex, layerindex);
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

void Controller::addCanvas(int animationindex, int frameindex)
{
    animations[animationindex]->addCanvas(frameindex);
}

void Controller::addFrame()
{
    activeAnimation->addFrame();
    activeAnimation->initializeFrame();
    updateScene();
}

void Controller::addFrameIndexed(int animationindex, int frameindex)
{
    animations[animationindex]->addFrameIndexed(frameindex);
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

void Controller::setActivePaintTool(PaintTool *t)
{
    scene->setActivePaintTool(t);
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
    Animation *a = new Animation(originalnumberofcolumns(),originalnumberofrows());
    a->initialize();
    activeAnimation = a;
    animations.append(a);
}

void Controller::addAnimation(int index)
{
    Animation *a = new Animation(originalnumberofcolumns(),originalnumberofrows());
    animations.insert(index,a);
}

void Controller::clearAll()
{
    foreach(Animation* a, animations)
    {
        a->clearAll();
    }
    while (!animations.isEmpty())
        delete animations.takeFirst();
}

QStringList Controller::getNameList()
{
    return nameList;
}

//a pixelscene összes adatát el kell menteni és le kell kérdezni, ha átjárhatóságot akarunk épületek között is!

void Controller::setoriginalnumberofcolumns(int r)
{

}

void Controller::setoriginalnumberofrows(int c)
{

}

void Controller::setNumberofrows(int animationindex, int frameindex, int layerindex, int number)
{
    animations[animationindex]->setNumberofrows(frameindex,layerindex,number);
}

void Controller::setNumberofcolumns(int animationindex, int frameindex, int layerindex, int number)
{
    animations[animationindex]->setNumberofcolumns(frameindex,layerindex,number);
}

void Controller::addLayerPixels(int animationindex, int frameindex, int layerindex, QString data)
{
    animations[animationindex]->addLayerPixels(frameindex,layerindex,data);
}

void Controller::updateCombinedLayers()
{
    foreach(Animation *a, animations)
        a->updateCombinedLayers();
}

void Controller::setDefaultActives()
{
    activeAnimation = animations[0];
    foreach(Animation *a, animations)
        a->setDefaultActives();
}

void Controller::importFile(QString fileName)
{
    importer->importFile(fileName);

    setDefaultActives();
    updateCombinedLayers();
    updateScene();
}

void Controller::exportFile(QString fileName)
{
    exporter->exportFile(fileName);
}

void Controller::playAnimation()
{
    playTool->play();
}

void Controller::pauseAnimation()
{
    playTool->Pause();
}

void Controller::stopAnimation()
{
    playTool->Stop();
}


#include "pixelscene.h"

PixelScene::PixelScene(QObject *parent) :
    QGraphicsScene(parent)
{
    primaryColor = Qt::white;
    secondaryColor = Qt::black;

    for(int i = 0; i < windowYNumber; i++)
    {
        for(int j = 0; j < windowXNumber; j++)
        {
            Window* w = new Window(this);
            for(int k = 0; k < windowHeight; k++)
            {
                for(int l = 0; l < windowWidth; l++)
                {
                    Pixel *p = new Pixel();
                    int x1 = j*windowWidth*pixelSize + j*gapWidth + l*pixelSize;
                    int x2 = j*windowWidth*pixelSize + j*gapWidth + (l+1)*pixelSize;
                    int y1 = i*windowHeight*pixelSize + i*gapHeight + k*pixelSize;
                    int y2 = i*windowHeight*pixelSize + i*gapHeight + (k+1)*pixelSize;
                    p->rect.adjust(x1,y1,x2,y2);
                    addItem(p);
                    p->window = w;
                    int index = i*windowWidth*windowHeight*windowXNumber + j*windowWidth + k*windowWidth*windowXNumber + l;
                    w->indexes.append(index);
                    p->index = index;
                    pixels.insert(index,p);
                }
            }
            windows.append(w);
        }
    }
    width = pixelSize * windowWidth * windowXNumber + gapWidth * (windowXNumber-1);
    height = pixelSize * windowHeight * windowYNumber + gapHeight * (windowYNumber-1);
    onlypixelswidth = pixelSize * windowWidth * windowXNumber;
    onlypixelsheight = pixelSize * windowHeight * windowYNumber;

    Canvas* c = new Canvas(pixels.size());
    activeCanvas = c;
    canvases.append(c);

    Frame* f = new Frame(c);
    frames.append(f);

    imageconverter = new ImageConverterTool(this, pixelSize, windowWidth * windowXNumber, windowHeight * windowYNumber);
    videoconverter = new VideoConverterTool(this);
    videoconverter->player->setNotifyInterval(interval);
}

PixelScene::~PixelScene()
{
    delete imageconverter;
    delete videoconverter;

    while (!pixels.isEmpty())
        delete pixels.takeFirst();
    while (!windows.isEmpty())
        delete windows.takeFirst();
    while (!canvases.isEmpty())
        delete canvases.takeFirst();
}

void PixelScene::destruct()
{
    while (!pixels.isEmpty())
        delete pixels.takeFirst();
    while (!windows.isEmpty())
        delete windows.takeFirst();
}

void PixelScene::mousePressEvent(QGraphicsSceneMouseEvent *e)
{
    activeTool->mousePressEvent(e,this);
}

void PixelScene::mouseMoveEvent(QGraphicsSceneMouseEvent *e)
{
    activeTool->mouseMoveEvent(e,this);
}

void PixelScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *e)
{
    activeTool->mouseReleaseEvent(e,this);
}

void PixelScene::updatePixel(int p)
{
    if(activeCanvas->activeLayer->pixels[p]->clear || activeCanvas->activeLayer->transparent)
        if(!activeCanvas->combinedLayer->pixels[p]->clear)
        {
            pixels[p]->brush->setColor(activeCanvas->combinedLayer->pixels[p]->color);
        }
        else
        {
            pixels[p]->brush->setColor(Qt::black);
        }
    else
        pixels[p]->brush->setColor(activeCanvas->activeLayer->pixels[p]->color);
    pixels[p]->update();
}

void PixelScene::updateCombinedLayer(int p)
{
    if(!activeCanvas->activeLayer->pixels[p]->clear && !activeCanvas->activeLayer->transparent)
    {
        activeCanvas->combinedLayer->pixels[p]->clear = false;
        activeCanvas->combinedLayer->pixels[p]->color = activeCanvas->activeLayer->pixels[p]->color;
    }
    else
    {
        int i = 0;
        while(i<activeCanvas->layers.size() && (activeCanvas->layers[i]->pixels[p]->clear || activeCanvas->layers[i]->transparent))
            i++;
        if(i==activeCanvas->layers.size())
        {
            activeCanvas->combinedLayer->pixels[p]->clear = true;
        }
        else
        {
            activeCanvas->combinedLayer->pixels[p]->clear = false;
            activeCanvas->combinedLayer->pixels[p]->color = activeCanvas->layers[i]->pixels[p]->color;
        }
    }
}

void PixelScene::updateScene()
{
    foreach(Pixel *p, pixels)
        updatePixel(p->index);
}

void PixelScene::updateCombined()
{
    foreach(Pixel *p, pixels)
        updateCombinedLayer(p->index);
}

void PixelScene::importImage(QImage image)
{
    switch(importsettingsresolution)
    {
        case PixelScene::ImportSettingsResolution::onlypixels:
            imageconverter->convertImage(image.scaled(onlypixelswidth+1,onlypixelsheight+1));
            break;
        case PixelScene::ImportSettingsResolution::wholeimage:
            imageconverter->convertImage(image.scaled(width+1,height+1));
            break;
    }
}

void PixelScene::importVideo(QString s)
{
    videoconverter->player->setMedia(QUrl::fromLocalFile(s));
    videoconverter->player->play();
}

Pixel *PixelScene::pixelUnderMouse()
{
    foreach(Pixel *p, pixels)
    {
        if(p->isUnderMouse())
            return p;
    }
    return NULL;
}

Pixel *PixelScene::containsPoint(float x, float y)
{
    foreach(Pixel *p, pixels)
    {
        if(p->rect.contains(x,y))
            return p;
    }
    return NULL;
}

//Megtalálja, és visszatér a legközelebbi pixellel.
Pixel *PixelScene::nearestPixel(float x, float y)
{
    //A maximális távolság a pixelek között. A keresőalgoritmus finomítja.
    float min = FLT_MAX;
    //Egyes pixelekkel számoláskor használt adatok:
    float distx, disty, distance;
    //A legközelebbi pixel
    Pixel *nearest;

    //A scene összes pixele közül megkeressük azt amelyik legközelebb van.
    foreach(Pixel *p, pixels)
    {
        distx = p->rect.center().x()-x;
        disty = p->rect.center().y()-y;
        distance = sqrtf(distx*distx + disty*disty);
        if(distance < min)
        {
            min = distance;
            nearest = p;
        }
    }
    return nearest;
}

void PixelScene::clearLayer()
{
    foreach(LayerPixel *lp, activeCanvas->activeLayer->pixels)
        lp->clear = true;
    for(int i=0; i<pixels.size(); i++)
    {
        updateCombinedLayer(i);
        updatePixel(i);
    }
}

void PixelScene::clearAll()
{
    foreach(Layer* l, activeCanvas->layers)
        delete l;
    activeCanvas->activeLayer = new Layer(pixels.size());
}

void PixelScene::addFrame()
{
    Canvas* c = new Canvas(pixels.size());
    activeCanvas = c;
    canvases.append(c);

    Frame* f = new Frame(c);
    frames.append(f);

    updateScene();
}

#include "pixelscene.h"
#include <QTextStream>

PixelScene::PixelScene(QObject *parent) :
    QGraphicsScene(parent)
{
    for(int i = 0; i < windowYNumber*windowXNumber*windowHeight*windowWidth; i++)
        pixels.append(new Pixel());
    for(int i = 0; i < windowYNumber; i++)
    {
        for(int j = 0; j < windowXNumber; j++)
        {
            Window* w = new Window();
            for(int k = 0; k < windowHeight; k++)
            {
                for(int l = 0; l < windowWidth; l++)
                {
                    int x1 = j*windowWidth*pixelSize + j*gapWidth + l*pixelSize;
                    int x2 = j*windowWidth*pixelSize + j*gapWidth + (l+1)*pixelSize;
                    int y1 = i*windowHeight*pixelSize + i*gapHeight + k*pixelSize;
                    int y2 = i*windowHeight*pixelSize + i*gapHeight + (k+1)*pixelSize;

                    int index = i*windowWidth*windowHeight*windowXNumber + j*windowWidth + k*windowWidth*windowXNumber + l;
                    pixels[index]->rect.adjust(x1,y1,x2,y2);
                    pixels[index]->window = w;
                    pixels[index]->index = index;
                    w->indexes.append(index);
                    addItem(pixels[index]);
                }
            }
            windows.append(w);
        }
    }
    onlypixelswidth = pixelSize * windowWidth * windowXNumber;
    onlypixelsheight = pixelSize * windowHeight * windowYNumber;
    width = onlypixelswidth + gapWidth * (windowXNumber-1);
    height = onlypixelsheight + gapHeight * (windowYNumber-1);
}

PixelScene::~PixelScene()
{
    while (!pixels.isEmpty())
        delete pixels.takeFirst();
    while (!windows.isEmpty())
        delete windows.takeFirst();
}

int PixelScene::originalnumberofcolumns()
{
    return windowXNumber*windowWidth;
}

int PixelScene::originalnumberofrows()
{
    return windowYNumber*windowHeight;
}

int PixelScene::numberofPixels()
{
    return pixels.size();
}

void PixelScene::mousePressEvent(QGraphicsSceneMouseEvent *e)
{
    activePaintTool->mousePressEvent(e);
}

void PixelScene::mouseMoveEvent(QGraphicsSceneMouseEvent *e)
{
    activePaintTool->mouseMoveEvent(e);
}

void PixelScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *e)
{
    activePaintTool->mouseReleaseEvent(e);
}

void PixelScene::updatePixel(int index, bool clear, QColor color)
{
    QTextStream(stdout) << index << endl;
    QTextStream(stdout) << pixels[index]->rect.x() << endl;
    QTextStream(stdout) << pixels[index]->rect.y() << endl;
    if(clear)
        pixels[index]->brush->setColor(Qt::black);
    else
        pixels[index]->brush->setColor(color);
    pixels[index]->update();
}

QList<int> PixelScene::windowIndexes(int index)
{
    return pixels[index]->window->indexes;
}

QColor PixelScene::getColorofPixel(int index)
{
    return pixels[index]->brush->color();
}

void PixelScene::setWindowToggled(bool checked)
{
    windowToggled = checked;
}

bool PixelScene::getWindowToggled()
{
    return windowToggled;
}

int PixelScene::getPixelSize()
{
    return pixelSize;
}

int PixelScene::getWidth()
{
    return width;
}

int PixelScene::getOnlyPixelsWidth()
{
    return onlypixelswidth;
}

int PixelScene::getHeight()
{
    return height;
}

int PixelScene::getOnlyPixelsHeight()
{
    return onlypixelsheight;
}

void PixelScene::setActivePaintTool(PaintTool *tool)
{
    activePaintTool = tool;
}

int PixelScene::pixelUnderMouse()
{
    foreach(Pixel *p, pixels)
    {
        if(p->isUnderMouse())
            return p->index;
    }
    return -1;
}

int PixelScene::containsPoint(float x, float y)
{
    foreach(Pixel *p, pixels)
    {
        if(p->rect.contains(x,y))
            return p->index;
    }
    return -1;
}

int PixelScene::nearestPixel(float x, float y)
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
    return nearest->index;
}

QRect PixelScene::getPixelRect(int index)
{
    return pixels[index]->rect;
}

void PixelScene::setoriginalnumberofcolumns()
{

}

void PixelScene::setoriginalnumberofrows()
{

}

//Megtalálja, és visszatér a legközelebbi pixellel.
QRect PixelScene::nearestPixelRect(float x, float y)
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
    return nearest->rect;
}

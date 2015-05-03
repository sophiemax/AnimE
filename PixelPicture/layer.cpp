#include "layer.h"

Layer::Layer(int r, int c)
{
    originalpixelsinarow = r;
    pixelsinarow = r;
    originalpixelsinacolumn = c;
    pixelsinacolumn = c;
    startindex = 0;
    for(int i = 0; i < r*c; i++)
    {
        LayerPixel *lp = new LayerPixel();
        lp->index = i;
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

void Layer::setColorofPixel(int i, QColor color)
{
    int index = calculateCurrentIndex(i);

    pixels[index]->clear = false;
    pixels[index]->color = color;
}

QColor Layer::getColorofPixel(int i)
{
    int index = calculateCurrentIndex(i);

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

bool Layer::isPixelClear(int i)
{
    int index = calculateCurrentIndex(i);
    return pixels[index]->clear;
}

void Layer::clearPixel(int i)
{
    int index = calculateCurrentIndex(i);
    pixels[index]->clear = true;
}

void Layer::clear()
{
    foreach(LayerPixel *lp, pixels)
    {
        lp->clear = true;
    }
}

void Layer::setStartIndex(int index)
{
    startindex = index;
}

int Layer::getStartIndex()
{
    return startindex;
}

void Layer::moveUp()
{

}

void Layer::moveDown()
{

}

void Layer::moveLeft()
{
    if(startindex % pixelsinarow == 0 && isFirstColumnClear())
    {
        for(int j = 0; j < pixelsinacolumn; j++)
        {
            for(int i = 1; i < pixelsinarow; i++)
            {
                pixels[j*pixelsinarow + i - 1]->clear = pixels[j*pixelsinarow + i]->clear;
                pixels[j*pixelsinarow + i - 1]->color = pixels[j*pixelsinarow + i]->color;
            }
        }
    }
    else
    {

    }
}

void Layer::moveRight()
{

}

bool Layer::isFirstColumnClear()
{
    bool clear = true;
    for(int i = 0; i < pixelsinarow * pixelsinacolumn; i += pixelsinarow)
        if(pixels[i]->clear == false)
            clear = false;
    return clear;
}

bool Layer::isLastColumnClear()
{
    bool clear = true;
    for(int i = pixelsinaRow; i < pixelsinarow * pixelsinacolumn; i += pixelsinarow)
        if(pixels[i]->clear == false)
            clear = false;
    return clear;
}

bool Layer::isFirstRowClear()
{
    bool clear = true;
    for(int i = 0; i < pixelsinarow; i++)
        if(pixels[i]->clear == false)
            clear = false;
    return clear;
}

bool Layer::isLastRowClear()
{
    bool clear = true;
    for(int i = pixelsinarow * (pixelsinacolumn-1); i < pixelsinarow * pixelsinacolumn; i++)
        if(pixels[i]->clear == false)
            clear = false;
    return clear;
}

int Layer::calculateCurrentIndex(int originalIndex)
{
    int originalrowofindex = originalIndex / originalpixelsinarow;
    int originalcolumnofindex = originalIndex - originalrowofindex * originalpixelsinarow;
    int startcolumnindex = startindex - (startindex / pixelsinarow) * pixelsinarow;;

    int index = startindex + originalrowofindex*pixelsinarow + startcolumnindex + originalcolumnofindex;

    return index;
}

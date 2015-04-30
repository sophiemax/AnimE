#include "layer.h"

Layer::Layer(int p)
{
    pixelNumber = p;
    for(int i = 0; i<p; i++)
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

#include "layerpixel.h"

LayerPixel::LayerPixel()
{

}

LayerPixel::LayerPixel(LayerPixel *lp)
{
    clear = lp->clear;
    color = lp->color;
    index = lp->index;
    //rect = lp->rect;
}

LayerPixel::~LayerPixel()
{

}


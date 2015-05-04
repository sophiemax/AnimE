#include "layerpixel.h"

LayerPixel::LayerPixel()
{

}

LayerPixel::LayerPixel(LayerPixel *lp)
{
    clear = lp->clear;
    color = lp->color;
    index = lp->index;
    if(index == 676)
    {
        QTextStream(stdout) << "yay" << endl;
        QTextStream(stdout) << clear << endl;
        QTextStream(stdout) << color.name() << endl;
        QTextStream(stdout) << "/yay" << endl;
    }
    //rect = lp->rect;
}

LayerPixel::~LayerPixel()
{

}


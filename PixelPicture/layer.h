#ifndef LAYER_H
#define LAYER_H

#include <QtGui>
#include <QtCore>
#include "layerpixel.h"

class Layer
{
public:
    Layer(int p);
    ~Layer();

    bool transparent = false;
    QList<LayerPixel*> pixels;
    int pixelNumber;
};

#endif // LAYER_H

#ifndef CANVAS_H
#define CANVAS_H

#include <QtGui>
#include <QtCore>
#include "layer.h"

class Canvas
{
public:
    Canvas(int p);
    ~Canvas();

    void updateCombinedLayer(int index);

    void addLayer(int i);
    void switchLayers(int i, int j);

    QList<Layer*> layers;
    Layer* combinedLayer;
    Layer* activeLayer;

    int pixelNumber;
};

#endif // CANVAS_H

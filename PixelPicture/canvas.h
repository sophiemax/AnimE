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

    void setLayerName(QString s);
    QString getLayerName();
    QString getLayerName(int index);

    void setLayerTransparency(bool t);

    void setActiveLayer(int index);

    void setColorofPixel(int index, QColor color);
    QColor getColorofPixel(int index);
    bool isPixelClear(int index);
    void clearPixel(int index);
    void clearLayer();
    void updateCombined();
    void updateCombinedLayer(int index);

    int numberofLayers();
    bool getTransparency(int index);

    void addLayer();
    void removeActiveLayer();
    void addLayer(int index);
    void switchLayers(int i, int j);

private:
    QList<Layer*> layers;
    Layer* combinedLayer;
    Layer* activeLayer;

    int numberofPixels;
};

#endif // CANVAS_H

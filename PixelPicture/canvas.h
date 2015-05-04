#ifndef CANVAS_H
#define CANVAS_H

#include <QtGui>
#include <QtCore>
#include "layer.h"

class Canvas
{
public:
    Canvas(int r, int c);
    Canvas(Canvas *c, int r, int col);
    ~Canvas();

    void setLayerName(QString s);
    QString getLayerName();
    QString getLayerName(int index);

    void setLayerTransparency(bool t);

    void setActiveLayer(int index);

    void setColorofPixel(int index, QColor color);
    QColor getColorofPixel(int index);
    QColor getColorofPixel(int layerindex, int pixelindex);
    bool isPixelClear(int index);
    bool isPixelClear(int layerindex, int pixelindex);
    void clearPixel(int index);
    void clearLayer();

    void moveLayerUp();
    void moveLayerDown();
    void moveLayerLeft();
    void moveLayerRight();

    void moveFrameUp();
    void moveFrameDown();
    void moveFrameLeft();
    void moveFrameRight();

    void updateCombined();
    void updateCombinedLayer(int index);

    int numberofLayers();
    bool getTransparency(int index);

    int getnumberofcolumns(int index);
    int getnumberofrows(int index);

    void addLayer();
    void removeActiveLayer();
    void addLayer(int index);
    void switchLayers(int i, int j);

    Layer *getLayer(int index);
    int getActive();

private:
    QList<Layer*> layers;
    Layer* combinedLayer;
    Layer* activeLayer;

    int pixelsinarow, pixelsinacolumn;
};

#endif // CANVAS_H

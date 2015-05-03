#ifndef LAYER_H
#define LAYER_H

#include <QtGui>
#include <QtCore>
#include "layerpixel.h"

class Layer
{
public:
    Layer(int r, int c);
    ~Layer();

    QString getName();
    void setName(QString s);

    void setColorofPixel(int i, QColor color);
    QColor getColorofPixel(int i);
    void setTransparency(bool t);
    bool getTransparency();
    bool isPixelClear(int i);
    void clearPixel(int i);
    void clear();

    void setStartIndex(int index);
    int getStartIndex();

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

    bool isFirstColumnClear();
    bool isLastColumnClear();
    bool isFirstRowClear();
    bool isLastRowClear();

    int calculateCurrentIndex(int originalIndex);

private:
    bool transparent = false;
    QList<LayerPixel*> pixels;

    int pixelsinarow, pixelsinacolumn;
    int originalpixelsinarow, originalpixelsinacolumn;
    int startindex;

    QString name;
};

#endif // LAYER_H

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

    QString getName();
    void setName(QString s);

    void setColorofPixel(int index, QColor color);
    QColor getColorofPixel(int index);
    void setTransparency(bool t);
    bool getTransparency();
    bool isPixelClear(int index);
    void clearPixel(int index);
    void clear();

private:
    bool transparent = false;
    QList<LayerPixel*> pixels;
    QString name;
};

#endif // LAYER_H

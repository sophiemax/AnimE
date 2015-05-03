#ifndef LAYERPIXEL_H
#define LAYERPIXEL_H

#include <QtGui>
#include <QtCore>

class LayerPixel
{
public:
    LayerPixel();
    ~LayerPixel();

    bool clear = true;
    QColor color;
    int index;
    QRect rect;
};

#endif // LAYERPIXEL_H

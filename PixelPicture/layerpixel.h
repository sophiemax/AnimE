#ifndef LAYERPIXEL_H
#define LAYERPIXEL_H

#include <QtGui>
#include <QtCore>

class LayerPixel
{
public:
    LayerPixel();
    LayerPixel(LayerPixel *lp);
    ~LayerPixel();

    //pixel átlátszósága
    bool clear = true;
    //pixel színe
    QColor color;
    //pixel indexe
    int index;
};

#endif // LAYERPIXEL_H

#ifndef FRAME_H
#define FRAME_H

#include <QtGui>
#include <QtCore>
#include "canvas.h"

class Frame
{
public:
    Frame(Canvas* c);
    ~Frame();

    Canvas *canvas;
    float timespan;
};

#endif // FRAME_H

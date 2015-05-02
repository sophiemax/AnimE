#ifndef FRAME_H
#define FRAME_H

#include <QtGui>
#include <QtCore>
#include "canvas.h"

class Frame
{
public:
    Frame();
    ~Frame();

    Canvas *canvas;
    float timespan = 1000.0;
};

#endif // FRAME_H

#ifndef WINDOW_H
#define WINDOW_H

#include <QtCore>
#include <QtGui>
#include <QList>
#include "pixel.h"

class Pixel;

class Window
{
public:
    Window();
    ~Window();

    QList<int> indexes;
};

#endif // WINDOW_H

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
    //ablak létrehozása
    Window();
    ~Window();

    //az ablakhoz tartozó pixelek indexei
    QList<int> indexes;
};

#endif // WINDOW_H

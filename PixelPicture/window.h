#ifndef WINDOW_H
#define WINDOW_H

#include <QtCore>
#include <QtGui>
#include <QList>
#include "pixel.h"
#include "pixelscene.h"
class PixelScene;
class Pixel;

class Window
{
public:
    Window(PixelScene* s);
    ~Window();

    PixelScene* scene;
    QList<int> indexes;

    void setWindowColor(QColor color);
    void clearWindow();
    void updateWindow();
};

#endif // WINDOW_H

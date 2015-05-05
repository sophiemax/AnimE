#ifndef PIXELSCENE_H
#define PIXELSCENE_H

#include <QtCore>
#include <QtGui>
#include "pixel.h"
#include "window.h"
#include "tool.h"

class Tool;

class PixelScene : public QGraphicsScene
{

public:

    PixelScene(QObject * parent = 0);
    ~PixelScene();
    void destruct();

    bool windowToggled = false;
    Tool *activeTool;

    int pixelsinaRow();
    int pixelsinaColumn();
    int numberofPixels();

    void mousePressEvent(QGraphicsSceneMouseEvent *e);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *e);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *e);

    void updatePixel(int index, bool clear, QColor color);

    QList<int> windowIndexes(int index);

    QColor getColorofPixel(int index);
    void setWindowToggled(bool checked);
    bool getWindowToggled();

    int getPixelSize();
    int getWidth();
    int getOnlyPixelsWidth();
    int getHeight();
    int getOnlyPixelsHeight();
    void setActiveTool(Tool* tool);

    int pixelUnderMouse();
    int containsPoint(float x, float y);
    int nearestPixel(float x, float y);
    QRect nearestPixelRect(float x, float y);
    QRect getPixelRect(int index);

    int width, height, onlypixelswidth, onlypixelsheight;

    QList<Pixel*> pixels;

    int pixelSize = 5;

    void setpixelsinarow();
    void setpixelsinacolumn();
    //int fps = 40;
    //float interval = 1000.0 / fps;
    //float timesum = 1000.0;

private:

    int gapWidth = 5, gapHeight = 15;
    int windowWidth = 2, windowHeight = 2, windowXNumber = 16, windowYNumber = 13;

    QList<Window*> windows;
};

#endif // PIXELSCENE_H

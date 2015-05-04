#ifndef FRAME_H
#define FRAME_H

#include <QtGui>
#include <QtCore>
#include "canvas.h"

class Frame
{
public:
    Frame(int r, int c);
    Frame(Frame* f, int r, int c);
    ~Frame();

    void setLayerName(QString s);
    QString getLayerName();
    QString getLayerName(int index);

    void setLayerTransparency(bool t);

    void setActiveLayer(int index);

    void addLayer();
    void removeActiveLayer();
    void switchLayers(int i, int j);

    int numberofLayers();

    void setColorofPixel(int index, QColor color);
    QColor getColorofPixel(int index);
    bool isPixelClear(int index);
    void clearPixel(int index);
    void clearLayer();

    void moveLayerUp();
    void moveLayerDown();
    void moveLayerLeft();
    void moveLayerRight();

    bool getTransparency(int index);

    float getTimespan();
    void setTimespan(float t);

    Canvas *getCanvas();

private:

    Canvas *canvas;

    float timespan = 1000.0;
};

#endif // FRAME_H

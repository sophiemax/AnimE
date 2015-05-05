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
    void setName(QString s);
    QString getName();

    void setLayerTransparency(bool t);

    void setActiveLayer(int index);

    void addLayer();
    void removeActiveLayer();
    void switchLayers(int i, int j);

    int numberofLayers();

    void setColorofPixel(int index, QColor color);
    QColor getColorofPixel(int index);
    QColor getColorofPixel(int layerindex, int pixelindex);
    bool isPixelClear(int index);
    bool isPixelClear(int layerindex, int pixelindex);
    void clearPixel(int index);
    void clearLayer();

    void moveLayerUp();
    void moveLayerDown();
    void moveLayerLeft();
    void moveLayerRight();

    void moveFrameUp();
    void moveFrameDown();
    void moveFrameLeft();
    void moveFrameRight();

    bool getTransparency(int index);

    int getnumberofcolumns(int index);
    int getnumberofrows(int index);

    float getTimespan();
    void setTimespan(float t);

    Canvas *getCanvas();

    void initialize();
    void initializeCanvas();
    void initializeLayer();

    void clearAll();

private:

    Canvas *canvas;

    float timespan = 1000.0;
    int pixelsinarow, pixelsinacolumn;
    QString name;
};

#endif // FRAME_H

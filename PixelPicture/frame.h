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
    void setLayerName(int layerindex, QString name);
    QString getLayerName();
    QString getLayerName(int index);
    void setName(QString s);
    QString getName();

    void setLayerTransparency(bool t);
    void setLayerTransparency(int layerindex, bool t);

    void setActiveLayer(int index);

    void addLayer();
    void addLayer(int index);
    void addCanvas();
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

    void setNumberofrows(int layerindex, int number);
    void setNumberofcolumns(int layerindex, int number);

    void addLayerPixels(int layerindex, QString data);

    void updateCombinedLayers();
    void setDefaultActives();

    //for debugging

    int getLayerSize();

private:

    Canvas *canvas;

    float timespan = 1000.0;
    int pixelsinarow, pixelsinacolumn;
    QString name;
};

#endif // FRAME_H

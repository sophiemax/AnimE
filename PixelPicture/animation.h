#ifndef ANIMATION_H
#define ANIMATION_H

#include "frame.h"

class Animation
{
public:
    Animation(int r, int c);
    ~Animation();

    void setLayerName(QString s);
    QString getLayerName();
    QString getLayerName(int index);
    QString getLayerName(int frameindex, int layerindex);

    void setFrameName(QString s);
    QString getFrameName();
    QString getFrameName(int index);

    void setName(QString s);
    QString getName();

    void setLayerTransparency(bool t);

    void setActiveLayer(int index);

    int numberofFrames();
    int numberofLayers();
    int numberofLayers(int index);
    int getnumberofrows(int frameindex, int layerindex);
    int getnumberofcolumns(int frameindex, int layerindex);
    void setActiveFrame(int index);
    void setNextFrameActive();
    float getCurrentTimespan();
    float getTimesum();
    float getTimespan(int index);
    float getCurrentTime();
    int getActiveFrameIndex();
    bool getTransparency(int index);
    bool getTransparency(int frameindex, int layerindex);

    void addLayer();
    void removeActiveLayer();
    void switchLayers(int i, int j);
    void addFrame();
    void addFrame(int t);
    void copyFrame();

    void moveLayerUp();
    void moveLayerDown();
    void moveLayerLeft();
    void moveLayerRight();

    void moveFrameUp();
    void moveFrameDown();
    void moveFrameLeft();
    void moveFrameRight();

    void setColorofPixel(int index, QColor color);
    QColor getColorofPixel(int index);
    QColor getColorofPixel(int frameindex, int layerindex, int pixelindex);
    bool isPixelClear(int index);
    bool isPixelClear(int frameindex, int layerindex, int pixelindex);
    void clearPixel(int index);
    void clearLayer();

private:
    float timesum = 0;
    int pixelsinarow, pixelsinacolumn;

    QList<Frame*> frames;
    Frame *activeFrame;

    QString name;
};

#endif // ANIMATION_H

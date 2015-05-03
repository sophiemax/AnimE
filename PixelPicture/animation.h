#ifndef ANIMATION_H
#define ANIMATION_H

#include "frame.h"

class Animation
{
public:
    Animation(int p);
    ~Animation();

    void setLayerName(QString s);
    QString getLayerName();
    QString getLayerName(int index);

    void setLayerTransparency(bool t);

    void setActiveLayer(int index);

    int numberofFrames();
    int numberofLayers();
    void setActiveFrame(int index);
    void setNextFrameActive();
    float getCurrentTimespan();
    float getTimesum();
    float getTimespan(int index);
    int getActiveFrameIndex();
    bool getTransparency(int index);

    void addLayer();
    void removeActiveLayer();
    void switchLayers(int i, int j);
    void addFrame();
    void addFrame(int t);
    void setColorofPixel(int index, QColor color);
    QColor getColorofPixel(int index);
    bool isPixelClear(int index);
    void clearPixel(int index);
    void clearLayer();

private:
    float timesum = 0;
    int numberofPixels;

    QList<Frame*> frames;
    Frame *activeFrame;
};

#endif // ANIMATION_H

#ifndef ANIMATION_H
#define ANIMATION_H

#include "frame.h"

class Animation
{
public:
    Animation(int r, int c);
    ~Animation();

    void setLayerName(QString s);
    void setLayerName(int frameindex, int layerindex, QString name);
    QString getLayerName();
    QString getLayerName(int index);
    QString getLayerName(int frameindex, int layerindex);

    void setFrameName(QString s);
    void setFrameName(int index, QString s);
    QString getFrameName();
    QString getFrameName(int index);

    void setName(QString s);
    QString getName();

    void setLayerTransparency(bool t);
    void setLayerTransparency(int frameindex, int layerindex, bool t);

    void setActiveLayer(int index);

    int numberofFrames();
    int numberofLayers();
    int numberofLayers(int index);
    int getnumberofrows(int frameindex, int layerindex);
    int getnumberofcolumns(int frameindex, int layerindex);
    void setActiveFrame(int index);
    void setNextFrameActive();
    float getCurrentTimespan();
    void setTimesum(float t);
    void setTimespan(int index, float t);
    float getTimesum();
    float getTimespan(int index);
    float getCurrentTime();
    int getActiveFrameIndex();
    bool getTransparency(int index);
    bool getTransparency(int frameindex, int layerindex);

    void addLayer();
    void addLayer(int frameindex, int layerindex);
    void removeActiveLayer();
    void switchLayers(int i, int j);
    void addCanvas(int index);
    void addFrame();
    void addFrame(int t);
    void addFrameIndexed(int index);
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

    void initialize();
    void initializeFrame();
    void initializeCanvas();
    void initializeLayer();

    void clearAll();

    void setNumberofrows(int frameindex, int layerindex, int number);
    void setNumberofcolumns(int frameindex, int layerindex, int number);

    void addLayerPixels(int frameindex, int layerindex, QString data);
    void updateCombinedLayers();
    void setDefaultActives();

    //for debugging
    int getLayerSize();

private:
    float timesum = 0;
    int pixelsinarow, pixelsinacolumn;

    QList<Frame*> frames;
    Frame *activeFrame;

    QString name;
};

#endif // ANIMATION_H

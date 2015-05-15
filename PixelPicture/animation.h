#ifndef ANIMATION_H
#define ANIMATION_H

#include "frame.h"

class Animation
{
public:
    Animation(int r, int c);
    ~Animation();

    //layer nevének lekérdezésére és módosítására
    void setLayerName(QString s);
    void setLayerName(int frameindex, int layerindex, QString name);
    QString getLayerName();
    QString getLayerName(int index);
    QString getLayerName(int frameindex, int layerindex);

    //frame nevének lekérdezésére és módosítására
    void setFrameName(QString s);
    void setFrameName(int index, QString s);
    QString getFrameName();
    QString getFrameName(int index);

    //az animáció nevének lekérdezésére és módosítására
    void setName(QString s);
    QString getName();

    //layer transparency beállítására
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

    //layer hozzáadása
    void addLayer();
    void addLayer(int frameindex, int layerindex);
    //layer eltávolítása
    void removeActiveLayer();
    //2 layer megcserélése
    void switchLayers(int i, int j);

    //canvas hozzáadása
    void addCanvas(int index);
    //frame hozzáadása
    void addFrame();
    void addFrame(int t);
    void addFrameIndexed(int index);
    //frame másolása
    void copyFrame();

    //layerek mozgatása
    void moveLayerUp();
    void moveLayerDown();
    void moveLayerLeft();
    void moveLayerRight();

    //framek mozgatása
    void moveFrameUp();
    void moveFrameDown();
    void moveFrameLeft();
    void moveFrameRight();

    // pixel színének lekérdezése és beállítása
    void setColorofPixel(int index, QColor color);
    QColor getColorofPixel(int index);
    QColor getColorofPixel(int frameindex, int layerindex, int pixelindex);

    //pixel clear változójának lekérdezése és beállítása
    bool isPixelClear(int index);
    bool isPixelClear(int frameindex, int layerindex, int pixelindex);
    void clearPixel(int index);

    //layer letisztítása
    void clearLayer();

    //létrehozás után adatokkal való feltöltés
    void initialize();
    void initializeFrame();
    void initializeCanvas();
    void initializeLayer();

    //az összes adat és változó törlése
    void clearAll();

    //a sorok illetve számának beállítása, egy bizonyos framen belüli bizonyos layerre.
    void setNumberofrows(int frameindex, int layerindex, int number);
    void setNumberofcolumns(int frameindex, int layerindex, int number);

    //layer pixelek hozzáadása betöltés alapján
    void addLayerPixels(int frameindex, int layerindex, QString data);
    //combinedLayer frissítése a megjelenítéshez.
    void updateCombinedLayers();
    //A felhasználói felület aktívvá tétele.
    void setDefaultActives();

    //for debugging
    int getLayerSize();

private:
    //az animáció összhossza
    float timesum = 0;

    //a kijelző oszlopainak és sorainak száma
    int originalnumberofcolumns, originalnumberofrows;

    //az animációhoz tartozó frame-ek és az aktív frame
    QList<Frame*> frames;
    Frame *activeFrame;

    //az animáció neve
    QString name;
};

#endif // ANIMATION_H

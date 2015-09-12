#ifndef FRAME_H
#define FRAME_H

#include <QtGui>
#include <QtCore>
#include "canvas.h"

class Frame
{
public:
    //frame létrehozása megadott sor és oszlopszámmal
    Frame(int r, int c);
    Frame(Frame* f, int r, int c);
    ~Frame();

    //layer nevének beállítása, lekérdezése
    void setLayerName(QString s);
    void setLayerName(int layerindex, QString name);
    QString getLayerName();
    QString getLayerName(int index);
    //a frame nevének beéllítása
    void setName(QString s);
    QString getName();

    //az aktív, vagy egy megadott layer láthatóságának módosítása
    void setLayerTransparency(bool t);
    void setLayerTransparency(int layerindex, bool t);

    //aktív layer beállítása
    void setActiveLayer(int index);

    //layer, canvas hozzáadása
    void addLayer();
    void addLayer(int index);
    void addCanvas();
    //aktív layer törlése
    void removeActiveLayer();
    //két layer cseréje
    void switchLayers(int i, int j);

    //layerek számának lekérdezése
    int numberofLayers();

    //pixel színének lekérdezése, beállítása egy megadott indexen
    void setColorofPixel(int index, QColor color);
    QColor getColorofPixel(int index);
    QColor getColorofPixel(int layerindex, int pixelindex);
    //pixel clear változójának lekérdezése, beállítása egy megadott indexen
    bool isPixelClear(int index);
    bool isPixelClear(int layerindex, int pixelindex);
    //megadott indexű pixel átlátszóvá tétele
    void clearPixel(int index);
    //aktív layer átlátszóvá tétele
    void clearLayer();

    //layerek mozgatása
    void moveLayerUp();
    void moveLayerDown();
    void moveLayerLeft();
    void moveLayerRight();

    //frame mozgatása
    void moveFrameUp();
    void moveFrameDown();
    void moveFrameLeft();
    void moveFrameRight();

    //láthatóság lekérdezése egy layer esetén
    bool getTransparency(int index);

    //sorok, oszlopok számának lekérdezése egy layer esetén
    int getnumberofcolumns(int index);
    int getnumberofrows(int index);

    //frame időtartamának lekérdezése, beállítása
    float getTimespan();
    void setTimespan(float t);

    //canvas lekérdezése
    Canvas *getCanvas();

    //létrehozás után feltöltés változókkal
    void initialize();
    void initializeCanvas();
    void initializeLayer();

    //az összes adat és változó törlése
    void clearAll();

    //sorok, oszlopok számának beállítása egy layer esetén
    void setNumberofrows(int layerindex, int number);
    void setNumberofcolumns(int layerindex, int number);

    //layer pixeleinek hozzáadása a betöltés során
    void addLayerPixels(int layerindex, QString data);

    //combinedlayer frissítése
    void updateCombinedLayers();
    //beállítja a program alapértelmezett fókuszát
    void setDefaultActives();

    //for debugging
    //lekérdezi a layer méretét
    int getLayerSize();

private:

    //a frame időtartama
    float timespan = 1000.0;

    //a kijelző oszlopainak és sorainak száma
    int originalnumberofcolumns, originalnumberofrows;

    //a frame-hez tartozó canvas
    Canvas *canvas;

    //frame neve
    QString name;
};

#endif // FRAME_H

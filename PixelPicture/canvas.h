#ifndef CANVAS_H
#define CANVAS_H

#include <QtGui>
#include <QtCore>
#include "layer.h"

class Canvas
{
public:
    //r-sor és c-oszlopszám alapján Canvas létrehozása
    Canvas(int r, int c);
    Canvas(Canvas *c, int r, int col);
    ~Canvas();

    //layer nevének beállítása
    void setLayerName(QString s);
    void setLayerName(int layerindex, QString name);
    QString getLayerName();
    QString getLayerName(int index);

    //layer átlátszóságának beállítása
    void setLayerTransparency(bool t);
    void setLayerTransparency(int layerindex, bool t);

    //aktív layer beállítása
    void setActiveLayer(int index);

    //pixel színének lekérdezése, beállítása, valamint a clear változó lekérdezése és beállítása.
    void setColorofPixel(int index, QColor color);
    QColor getColorofPixel(int index);
    QColor getColorofPixel(int layerindex, int pixelindex);
    bool isPixelClear(int index);
    bool isPixelClear(int layerindex, int pixelindex);
    void clearPixel(int index);
    void clearLayer();

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

    //megjelenítés frissítése
    void updateCombined();
    void updateCombinedLayer(int index);

    //layerek számának lekérdezése.
    int numberofLayers();
    //láthatóság lekérdezése
    bool getTransparency(int index);

    //sorok illetve oszlopok számának lekérdezése a bizonyos számú layeren
    int getnumberofcolumns(int index);
    int getnumberofrows(int index);

    //layer hozzáadása
    void addLayer();
    void addLayer(int index);
    //layer eltávolítása
    void removeActiveLayer();
    //két layer cseréje
    void switchLayers(int i, int j);

    //bizonyos indexű layer lekérdezése
    Layer *getLayer(int index);
    int getActive();

    //létrehozás után adatokkal való feltöltés
    void initialize();
    void initializeLayer();

    //az összes adat és változó törlése
    void clearAll();

    //sorok illetve oszlopok számának beállítása egy bizonyos layeren.
    void setNumberofrows(int layerindex, int number);
    void setNumberofcolumns(int layerindex, int number);

    //layerpixelek hozzáadása betöltés során
    void addLayerPixels(int layerindex, QString data);

    //felhasználói felület fókuszának beállítása
    void setDefaultActives();

    //for debugging
    int getLayerSize();

private:

    //a kijelző oszlopainak és sorainak száma
    int originalnumberofcolumns, originalnumberofrows;

    //a frame-hez tartozó layerek és az aktív layer
    QList<Layer*> layers;
    Layer* activeLayer;

    //a layerek összesítése
    Layer* combinedLayer;
};

#endif // CANVAS_H

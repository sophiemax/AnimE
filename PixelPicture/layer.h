#ifndef LAYER_H
#define LAYER_H

#include <QtGui>
#include <QtCore>
#include "layerpixel.h"

class Layer
{
public:
    //layer létrehozása megadott sor és oszlopszámmal
    Layer(int r, int c);
    Layer(Layer *l, int r, int c);
    ~Layer();

    //név beállítása
    QString getName();
    void setName(QString s);

    //megadott indexű pixel színének beállítása, lekérdezése
    void setColorofPixel(int i, QColor color);
    QColor getColorofPixel(int i);
    QColor getColorofLayerPixel(int index);
    //layer láthatóság beállítása, lekérdezése
    void setTransparency(bool t);
    bool getTransparency();
    //pixel clear értékének lekérdezése, beállítása
    bool isPixelClear(int i);
    bool isLayerPixelClear(int index);
    void clearPixel(int i);
    void clear();

    //a kijelző kezdő pixelindexének beállítása, lekérdezése
    void setStartIndex(int index);
    int getStartIndex();

    //oszlopok, sorok számának lekérdezése, beállítása
    int getNumberofColumns();
    int getNumberofRows();
    void setNumberofrows(int number);
    void setNumberofcolumns(int number);
    //layer méretének lekérdezése
    int getSize();

    //bizonyos indexű layerpixel lekérdezése
    LayerPixel *getLayerPixel(int index);

    //layer mozgatása
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

    //első,utolsó sor,oszlop ürességének lekérdezése
    bool isFirstColumnClear();
    bool isLastColumnClear();
    bool isFirstRowClear();
    bool isLastRowClear();

    //megállapítja egy pixel indexe alapján, hogy első/utolsó sorban/oszlopban van-e
    bool isinFirstColumn(int index);
    bool isinLastColumn(int index);
    bool isinFirstRow(int index);
    bool isinLastRow(int index);

    //kiszíámítja a sor, és oszlop, illetve az eredeti index alapján a jelenlegi (megjelenítés szempontjából érdekes) indexet
    int calculateCurrentIndex(int originalIndex);
    int calculateCurrentIndex(int row, int column);

    //létrehozáskor adatokkal, és változókkal feltöltés
    void initialize();
    void clearAll();

    //betöltéskor layerpixelek hozzáadása
    void addLayerPixels(QString data);

private:

    //a layer oszlopainak és sorainak száma
    int numberofcolumns, numberofrows;
    //a kijelző oszlopainak és sorainak száma
    int originalnumberofcolumns, originalnumberofrows;
    //layerpixel indexe, ahol a kijelző kezdődik
    int startindex;

    //a layer átlátszósága
    bool transparent = false;

    //a layerhez tartozó pixelek
    QList<LayerPixel*> pixels;

    //a layer neve
    QString name;
};

#endif // LAYER_H

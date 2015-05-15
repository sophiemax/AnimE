#ifndef LAYER_H
#define LAYER_H

#include <QtGui>
#include <QtCore>
#include "layerpixel.h"

class Layer
{
public:
    Layer(int r, int c);
    Layer(Layer *l, int r, int c);
    ~Layer();

    QString getName();
    void setName(QString s);

    void setColorofPixel(int i, QColor color);
    QColor getColorofPixel(int i);
    QColor getColorofLayerPixel(int index);
    void setTransparency(bool t);
    bool getTransparency();
    bool isPixelClear(int i);
    bool isLayerPixelClear(int index);
    void clearPixel(int i);
    void clear();

    void setStartIndex(int index);
    int getStartIndex();

    int getNumberofColumns();
    int getNumberofRows();
    void setNumberofrows(int number);
    void setNumberofcolumns(int number);
    int getSize();

    LayerPixel *getLayerPixel(int index);

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

    bool isFirstColumnClear();
    bool isLastColumnClear();
    bool isFirstRowClear();
    bool isLastRowClear();

    bool isinFirstColumn(int index);
    bool isinLastColumn(int index);
    bool isinFirstRow(int index);
    bool isinLastRow(int index);

    int calculateCurrentIndex(int originalIndex);
    int calculateCurrentIndex(int row, int column);

    void initialize();
    void clearAll();

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

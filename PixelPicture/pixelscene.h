#ifndef PIXELSCENE_H
#define PIXELSCENE_H

#include <QtCore>
#include <QtGui>
#include "pixel.h"
#include "window.h"
#include "painttool.h"

class PaintTool;

class PixelScene : public QGraphicsScene
{

public:
    PixelScene(QObject * parent = 0);
    ~PixelScene();

    //lekérdezi a kijelző oszlopainak/sorainak számát
    int originalnumberofcolumns();
    int originalnumberofrows();
    //lekérdezi a pixelek számát
    int numberofPixels();

    //egérműveletek lekezelését szolgáló függvények
    void mousePressEvent(QGraphicsSceneMouseEvent *e);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *e);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *e);

    //az adott indexű pixelt a kapott paraméterekkel frissíti
    void updatePixel(int index, bool clear, QColor color);

    //lekérdezi, hogy az adott indexű pixel ablakához mely indexű pixelek tartoznak
    QList<int> windowIndexes(int index);

    //lekérdezi az adott indexű pixel színét
    QColor getColorofPixel(int index);

    //beállítja/lekérdezi, hogy a kijelző aktuálisan pixelenként, vagy ablakonként módosítható
    void setWindowToggled(bool checked);
    bool getWindowToggled();

    //lekérdezi a pixelméretet
    int getPixelSize();
    //lekérdezi a kijelző szélességét lyukakkal, vagy anélkül
    int getWidth();
    int getOnlyPixelsWidth();
    //lekérdezi a kijelző magasságát lyukakkal, vagy anélkül
    int getHeight();
    int getOnlyPixelsHeight();

    //beállítja az aktív rajzeszközt
    void setActivePaintTool(PaintTool* tool);

    //megállapítja, hogy egy adott koordinátán (vagy az egér pozíciójában) van-e pixel
    int pixelUnderMouse();
    int containsPoint(float x, float y);
    //megkeresi a legközelebbi pixelt a megadott koordinátához, és visszatér annak indexével, vagy az őt definiáló téglalappal
    int nearestPixel(float x, float y);
    QRect nearestPixelRect(float x, float y);
    //lekérdezi a megadott indexű pixelt definiáló téglalapot
    QRect getPixelRect(int index);    

    //beállítja a kijelző oszlopainak/sorainak számát
    void setoriginalnumberofcolumns();
    void setoriginalnumberofrows();

private:

    //kijelzőpixelméret pixelben megadva
    int pixelSize = 3;
    //az ablakok közötti lyukak pixelben megadva
    int gapWidth = 5, gapHeight = 15;
    //az ablak szélessége és magassága kijelzőpixelben megadva
    int windowWidth = 3, windowHeight = 3;
    //az ablakok száma vízszintesen és fü;ggőlegesen
    int windowXNumber = 16, windowYNumber = 13;
    //a kijelző szélessége és magassága pixelben (lyukakkal, és anélkül)
    int width, height, onlypixelswidth, onlypixelsheight;

    //ablak, vagy pixelszinten módosítunk
    bool windowToggled = false;
    //az aktív painttool
    PaintTool *activePaintTool;

    //pixelek és ablakok eltárolása
    QList<Pixel*> pixels;
    QList<Window*> windows;
};

#endif // PIXELSCENE_H

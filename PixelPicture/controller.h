#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "pixelscene.h"
#include "animation.h"
#include "imageconvertertool.h"
#include "videoconvertertool.h"
#include "importtool.h"
#include "exporttool.h"
#include "playtool.h"
#include "painttool.h"

class ImageConverterTool;
class VideoConverterTool;
class ImportTool;
class ExportTool;
class PixelScene;
class PlayTool;
class PaintTool;

class Controller
{
public:
    Controller(PixelScene *s);
    ~Controller();

    //lekérdezi a kijelző oszlopainak/sorainak számát
    int originalnumberofcolumns();
    int originalnumberofrows();
    //lekérezi a kijelzőn lévő pixelek számát
    int numberofPixels();
    //lekérdezi a kijelző méretét, illetve a kijelző pixeleinek a méretét, a köztes területeket nem számolva
    int getWidth();
    int getOnlyPixelsWidth();
    int getHeight();
    int getOnlyPixelsHeight();

    //lekérdezi az animációk, framek, layerek számát.
    int numberofAnimations();
    int numberofFrames();
    int numberofFrames(int index);
    int numberofLayers();
    int numberofLayers(int animationindex, int frameindex);

    //lekérdezi a sorok illetve oszlopok számát egy indexekkel definiált layer esetén
    int getnumberofrows(int animationindex, int frameindex, int layerindex);
    int getnumberofcolumns(int animationindex, int frameindex, int layerindex);

    //beállítja az aktív framet, layert
    void setActiveFrame(int index);
    void setNextFrameActive();
    void setActiveLayer(int index);
    //beállítja egy az aktív layer, vagy egy indexekkel definiált layer átlátszóságát
    bool getTransparency(int index);
    bool getTransparency(int animationindex, int frameindex, int layerindex);
    //lekérdezi, illetve beállítja az animáció időterjedelmét
    float getCurrentTimespan();
    void setTimesum(int index, float t);
    float getTimesum();
    float getTimesum(int index);
    void setTimespan(int animationindex, int frameindex, float t);
    float getTimespan(int index);
    float getTimespan(int animationindex, int frameindex);
    //lekérdezi az aktuális időt
    float getCurrentTime();
    //lekérdezi az aktív frame indexét
    int getActiveFrameIndex();

    ImageConverterTool *getImageConverter();

    //beálítja, lekérdezi egy az aktív layer vagy egy indexekkel megadott layer/frame/animation nevét
    void setLayerName(QString s);
    void setLayerName(int animationindex, int frameindex, int layerindex, QString name);
    QString getLayerName();
    QString getLayerName(int index);
    QString getLayerName(int animationindex, int frameindex, int layerindex);
    void setFrameName(QString s);
    void setFrameName(int animationindex, int frameindex, QString name);
    QString getFrameName();
    QString getFrameName(int index);
    QString getFrameName(int animationindex, int frameindex);    
    void setAnimationName(int index, QString s);
    QString getAnimationName(int index);

    //beállítja egy layer láthatóságát
    void setLayerTransparency(bool t);
    void setLayerTransparency(int animationindex, int frameindex, int layerindex, bool t);
    //layer hozzáadása az aktív framehez, vagy egy megadott indexre
    void addLayer();
    void addLayer(int animationindex, int frameindex, int layerindex);
    //aktív layer törlése
    void removeActiveLayer();
    //két layer cseréje az aktív framen.
    void switchLayers(int i, int j);
    //új canvas hozzáadása a kiválasztott framehez.
    void addCanvas(int animationindex, int frameindex);
    //frame hozzáadása az aktív animációhoz, vagy egy kiválasztott indexre
    void addFrame();
    void addFrameIndexed(int animationindex, int frameindex);
    void addFrame(int timespan);
    //frame másolása
    void copyFrame();

    //layer mozgatása
    void moveLayerUp();
    void moveLayerDown();
    void moveLayerLeft();
    void moveLayerRight();

    //frame mozgatása
    void moveFrameUp();
    void moveFrameDown();
    void moveFrameLeft();
    void moveFrameRight();

    //pixel színének beállítása
    void setColorofPixel(int index);
    void setColorofPixel(int index, QColor color);
    void setColorofPixelFill(int index);
    QColor getColorofPixel(int index);
    QColor getColorofPixel(int animationindex, int frameindex, int layerindex, int pixelindex);
    //festőszínek beállítása, lekérdezése
    void setPrimaryColor(QColor color);
    QColor getPrimaryColor();
    void setSecondaryColor(QColor color);
    QColor getSecondaryColor();
    //aktív festő eszköz lekérdezése
    void setActivePaintTool(PaintTool *t);
    //beállítja hogy ablak vagy pixel szinten módosítunk
    void setWindowToggled(bool toggled);

    //lekérdezi a CombinedLayer pixelének clear változóját, beállítja egy ixel színét
    bool isCombinedLayerPixelClear(int index);
    QColor getColorofCombinedLayerPixel(int index);
    void clearPixel(int index);
    void clearLayer();

    //lekérdezi egy pixel clear változóját
    bool isPixelClear(int animationindex, int frameindex, int layerindex, int pixelindex);

    //kép illetve videó beimportálása
    void importImage(QImage image);
    void importVideo(QString fileName);

    //megállapítja hogy egy adott koordinátán (vagy az egér pozíciójában) van e pixel.
    int pixelUnderMouse();
    int containsPoint(float x, float y);
    //megkeresi a legközelebbi pixelt a megadott koordinátához, és visszatér annak indexélvel, vagy az őt definiáló téglappal.
    int nearestPixel(float x, float y);
    QRect nearestPixelRect(float x, float y);
    //lekérdezi a megadott indexű pixelt definiáló téglalapot
    QRect getPixelRect(int index);

    //pixelméret lekérdezése
    int getPixelSize();
    //frissíti a megjelenítést
    void updateScene();

    //animáció hozzáadása
    void addAnimation();
    void addAnimation(int index);

    //az összes tagváltozó törlése
    void clearAll();

    //exportálás és importálás esetén a névlistát adja vissza
    QStringList getNameList();

    //kijelző oszlop/sorszámának beállítása
    void setoriginalnumberofcolumns(int r);
    void setoriginalnumberofrows(int c);

    //oszlopok és sorok számának beállítása egy adott layer esetén
    void setNumberofrows(int animationindex, int frameindex, int layerindex, int number);
    void setNumberofcolumns(int animationindex, int frameindex, int layerindex, int number);

    //importálás esetén hozzáadja a megadott layerhez a betöltött pixeleket
    void addLayerPixels(int animationindex, int frameindex, int layerindex, QString data);
    //frissíti a combinedlayereket
    void updateCombinedLayers();
    //beállítja a program fókuszát az alapértelmezett állásba
    void setDefaultActives();

    //Fájl importálása, exportálása
    void importFile(QString fileName);
    void exportFile(QString fileName);

    //animáció lejátszása
    void playAnimation();

private:
    //a kijelzőpixelek megjelenítéséhez, adatok lekéréséhez és módosításához
    PixelScene *scene;

    //az animációk és az aktív animáció
    QList<Animation*> animations;
    Animation *activeAnimation;

    //az elsődleges és a másodlagos szín
    QColor primaryColor, secondaryColor;

    //export és import névlista
    QStringList nameList;

    //kép- és videókonvertáló eszköz
    ImageConverterTool *imageconverter;
    VideoConverterTool *videoconverter;

    //export és import eszköz
    ExportTool *exporter;
    ImportTool *importer;

    //animáció lejátszásához szükséges eszköz
    PlayTool* playTool;
};

#endif // CONTROLLER_H

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

    int originalnumberofcolumns();
    int originalnumberofrows();
    int numberofPixels();
    int getWidth();
    int getOnlyPixelsWidth();
    int getHeight();
    int getOnlyPixelsHeight();

    int numberofAnimations();
    int numberofFrames();
    int numberofFrames(int index);
    int numberofLayers();
    int numberofLayers(int animationindex, int frameindex);

    int getnumberofrows(int animationindex, int frameindex, int layerindex);
    int getnumberofcolumns(int animationindex, int frameindex, int layerindex);

    void setActiveFrame(int index);
    void setNextFrameActive();
    void setActiveLayer(int index);
    bool getTransparency(int index);
    bool getTransparency(int animationindex, int frameindex, int layerindex);
    float getCurrentTimespan();
    void setTimesum(int index, float t);
    float getTimesum();
    float getTimesum(int index);
    void setTimespan(int animationindex, int frameindex, float t);
    float getTimespan(int index);
    float getTimespan(int animationindex, int frameindex);
    float getCurrentTime();
    int getActiveFrameIndex();

    ImageConverterTool *getImageConverter();

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

    void setLayerTransparency(bool t);
    void setLayerTransparency(int animationindex, int frameindex, int layerindex, bool t);
    void addLayer();
    void addLayer(int animationindex, int frameindex, int layerindex);
    void removeActiveLayer();
    void switchLayers(int i, int j);
    void addCanvas(int animationindex, int frameindex);
    void addFrame();
    void addFrameIndexed(int animationindex, int frameindex);
    void addFrame(int timespan);
    void copyFrame();

    void moveLayerUp();
    void moveLayerDown();
    void moveLayerLeft();
    void moveLayerRight();

    void moveFrameUp();
    void moveFrameDown();
    void moveFrameLeft();
    void moveFrameRight();

    void setColorofPixel(int index);
    void setColorofPixel(int index, QColor color);
    void setColorofPixelFill(int index);
    QColor getColorofPixel(int index);
    QColor getColorofPixel(int animationindex, int frameindex, int layerindex, int pixelindex);
    void setPrimaryColor(QColor color);
    QColor getPrimaryColor();
    void setSecondaryColor(QColor color);
    QColor getSecondaryColor();
    void setActivePaintTool(PaintTool *t);
    void setWindowToggled(bool toggled);

    bool isCombinedLayerPixelClear(int index);
    QColor getColorofCombinedLayerPixel(int index);
    void clearPixel(int index);
    void clearLayer();

    bool isPixelClear(int animationindex, int frameindex, int layerindex, int pixelindex);

    void importImage(QImage image);
    void importVideo(QString fileName);

    int pixelUnderMouse();
    int containsPoint(float x, float y);
    int nearestPixel(float x, float y);
    QRect nearestPixelRect(float x, float y);
    QRect getPixelRect(int index);

    int getPixelSize();
    void updateScene();

    void addAnimation();
    void addAnimation(int index);

    void clearAll();

    QStringList getNameList();

    void setoriginalnumberofcolumns(int r);
    void setoriginalnumberofrows(int c);

    void setNumberofrows(int animationindex, int frameindex, int layerindex, int number);
    void setNumberofcolumns(int animationindex, int frameindex, int layerindex, int number);

    void addLayerPixels(int animationindex, int frameindex, int layerindex, QString data);
    void updateCombinedLayers();
    void setDefaultActives();

    void importFile(QString fileName);
    void exportFile(QString fileName);

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

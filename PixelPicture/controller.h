#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "pixelscene.h"
#include "animation.h"
#include "imageconvertertool.h"
#include "videoconvertertool.h"
#include "tool.h"

class ImageConverterTool;
class VideoConverterTool;
class PixelScene;
class Tool;

class Controller
{
public:
    Controller(PixelScene *s);
    ~Controller();

    int pixelsinaRow();
    int pixelsinaColumn();
    int numberofPixels();
    int getWidth();
    int getOnlyPixelsWidth();
    int getHeight();
    int getOnlyPixelsHeight();

    int numberofFrames();
    int numberofLayers();
    void setActiveFrame(int index);
    void setNextFrameActive();
    void setActiveLayer(int index);
    bool getTransparency(int index);
    float getCurrentTimespan();
    float getTimesum();
    float getTimespan(int index);
    int getActiveFrameIndex();

    ImageConverterTool *getImageConverter();

    void setLayerName(QString s);
    QString getLayerName();
    QString getLayerName(int index);
    void setLayerTransparency(bool t);
    void addLayer();
    void removeActiveLayer();
    void switchLayers(int i, int j);
    void addFrame();
    void addFrame(int timespan);
    void copyFrame();

    void setColorofPixel(int index);
    void setColorofPixel(int index, QColor color);
    QColor getColorofPixel(int index);
    void setPrimaryColor(QColor color);
    QColor getPrimaryColor();
    void setSecondaryColor(QColor color);
    QColor getSecondaryColor();
    void setActiveTool(Tool *tool);
    void setWindowToggled(bool toggled);

    bool isCombinedLayerPixelClear(int index);
    QColor getColorofCombinedLayerPixel(int index);
    void clearPixel(int index);
    void clearLayer();

    void importImage(QImage image);
    void importVideo(QString fileName);

    int pixelUnderMouse();
    int containsPoint(float x, float y);
    int nearestPixel(float x, float y);
    QRect nearestPixelRect(float x, float y);
    QRect getPixelRect(int index);

    int getPixelSize();
    void updateScene();

private:
    PixelScene *scene;

    QList<Animation*> animations;
    Animation *activeAnimation;

    QColor primaryColor, secondaryColor;

    ImageConverterTool *imageconverter;
    VideoConverterTool *videoconverter;
};

#endif // CONTROLLER_H

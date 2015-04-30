#ifndef PIXELSCENE_H
#define PIXELSCENE_H

#include <QtCore>
#include <QtGui>
#include "pixel.h"
#include "window.h"
#include "tool.h"
#include "canvas.h"
#include "imageconvertertool.h"
#include "videoconvertertool.h"
#include "frame.h"

class Tool;
class Window;
class Pixel;
class ImageConverterTool;
class VideoConverterTool;

class PixelScene : public QGraphicsScene
{
    Q_ENUMS(ImportSetting)
public:

    enum class ImportSettingsResolution
      {
         onlypixels,
         wholeimage
      };

    PixelScene(QObject * parent = 0);
    ~PixelScene();
    void destruct();

    QColor primaryColor, secondaryColor;
    bool windowToggled = false;
    Tool *activeTool;
    Canvas* activeCanvas;

    void mousePressEvent(QGraphicsSceneMouseEvent *e);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *e);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *e);

    void updatePixel(int p);
    void updateCombinedLayer(int p);
    void updateScene();
    void updateCombined();

    void importImage(QImage image);
    void importVideo(QString s);

    Pixel *pixelUnderMouse();
    Pixel *containsPoint(float x, float y);
    Pixel *nearestPixel(float x, float y);

    void clearLayer();
    void clearAll();

    void addFrame();

    int width, height, onlypixelswidth, onlypixelsheight;

    QList<Pixel*> pixels;
    QList<Frame*> frames;

    int pixelSize = 5;
    int fps = 40;
    float interval = 1000.0 / fps;
    float timesum = 1000.0;

    ImportSettingsResolution importsettingsresolution = PixelScene::ImportSettingsResolution::onlypixels;

    ImageConverterTool *imageconverter;
    VideoConverterTool *videoconverter;

private:

    int gapWidth = 5, gapHeight = 15;
    int windowWidth = 2, windowHeight = 2, windowXNumber = 16, windowYNumber = 13;

    QList<Window*> windows;
    QList<Canvas*> canvases;
};

#endif // PIXELSCENE_H

#ifndef VIDEOCONVERTERTOOL_H
#define VIDEOCONVERTERTOOL_H

#include <QMediaPlayer>
#include "pixelscene.h"
#include "videosurface.h"

class PixelScene;
class VideoSurface;

class VideoConverterTool
{
public:
    //a videoconvertertool létrehozása a megfelelő controller pointerrel
    VideoConverterTool(Controller *c);
    ~VideoConverterTool();

    //új videó esetén a szükséges változókat nullába állítja
    void reset();
    //beállítja a kapott videót a player tartalmának
    void setMedia(QMediaContent content);
    //elindítja a player lejátszását
    void start();

    void settings(bool trim, int from, int to);

private:
    //módosítások lekommunikálásához
    Controller *controller;

    //a lejátszást végrehajtó player
    QMediaPlayer *player;
    //a feldolgozást végrehajtó surface
    VideoSurface *surface;
};

#endif // VIDEOCONVERTERTOOL_H

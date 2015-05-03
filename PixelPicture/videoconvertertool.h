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
    VideoConverterTool(Controller *c);
    ~VideoConverterTool();

    void reset();
    void setMedia(QMediaContent content);
    void start();

private:
    Controller *controller;

    QMediaPlayer *player;
    VideoSurface *surface;
};

#endif // VIDEOCONVERTERTOOL_H

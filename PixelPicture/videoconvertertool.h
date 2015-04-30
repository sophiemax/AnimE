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
    VideoConverterTool(PixelScene *s);
    ~VideoConverterTool();

    QMediaPlayer *player;
    VideoSurface *surface;
private:
    PixelScene *scene;
};

#endif // VIDEOCONVERTERTOOL_H

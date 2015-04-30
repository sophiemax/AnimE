#include "videoconvertertool.h"

VideoConverterTool::VideoConverterTool(PixelScene *s)
{
    player = new QMediaPlayer;
    scene = s;
    surface = new VideoSurface(s);
    player->setVideoOutput(surface);
}

VideoConverterTool::~VideoConverterTool()
{

}


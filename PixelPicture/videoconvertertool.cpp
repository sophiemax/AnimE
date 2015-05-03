#include "videoconvertertool.h"

VideoConverterTool::VideoConverterTool(Controller *c)
{
    player = new QMediaPlayer;
    controller = c;
    surface = new VideoSurface(c, player);
    player->setVideoOutput(surface);
}

VideoConverterTool::~VideoConverterTool()
{
    delete player;
    delete surface;
}

void VideoConverterTool::reset()
{
    surface->reset();
}

void VideoConverterTool::setMedia(QMediaContent content)
{
    player->setMedia(content);
}

void VideoConverterTool::start()
{
    player->play();
}


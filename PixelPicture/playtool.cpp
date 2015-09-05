#include "playtool.h"
#include <QElapsedTimer>

PlayTool::PlayTool(Controller* c)
{
    controller = c;
    connect(&timer, &QTimer::timeout, this, &PlayTool::updateScene);
    connect(&timer, &QTimer::timeout, this, &PlayTool::updateSlider);
    timer.setSingleShot(true);
}

PlayTool::~PlayTool()
{

}

void PlayTool::play()
{
    i = 0;
    timesum = 0.0;
    updateScene();
}

void PlayTool::Pause()
{
    timer.stop();
}

void PlayTool::updateScene()
{
    if (i < controller->numberofFrames())
    {
        controller->setActiveFrame(i);
        timer.start(controller->getTimespan(i));
        timesum += controller->getTimespan(i);
        ++i;
    }
}

void PlayTool::updateSlider()
{
    emit positionChanged(timesum);
}

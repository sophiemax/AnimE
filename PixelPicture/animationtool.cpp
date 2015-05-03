#include "animationtool.h"
#include <QElapsedTimer>

AnimationTool::AnimationTool(Controller* c)
{
    controller = c;
    connect(&timer, &QTimer::timeout, this, &AnimationTool::updateScene);
    connect(&timer, &QTimer::timeout, this, &AnimationTool::updateSlider);
    timer.setSingleShot(true);
}

AnimationTool::~AnimationTool()
{

}

void AnimationTool::play()
{
    i = 0;
    timesum = 0.0;
    updateScene();
}

void AnimationTool::updateScene()
{
    if (i < controller->numberofFrames())
    {
        controller->setActiveFrame(i);
        timesum += controller->getTimespan(i);
        timer.start(controller->getTimespan(i));
        ++i;
    }
}

void AnimationTool::updateSlider()
{
    emit positionChanged(timesum);
}

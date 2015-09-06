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
    float animTSum = controller->getTimesum();
    //ha az eltelt idő több, mint az animáció teljes hossza - 10 ms, akkor
    //úgy értelmezzük, hogy vége van, és újraindítjuk az animációt
    if(timesum > animTSum - 10)
    {
        i = 0;
        timesum = 0.0;
    }
    updateScene();
}

void PlayTool::Pause()
{
    timer.stop();
}

void PlayTool::Stop()
{
    timer.stop();
    i = 0;
    timesum = 0.0;
    controller->setActiveFrame(i);
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

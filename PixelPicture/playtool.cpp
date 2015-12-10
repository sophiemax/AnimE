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
    playSpeed = 1.0;
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
    if (i < controller->numberofFrames() && i >= 0)
    {
        controller->setActiveFrame(i);
        // a timer-t elosztjuk a playSpeeddel, hogy annyival gyorsítssuk a lejátszás sepességét
        timer.start(controller->getTimespan(i) / fabs(playSpeed));
        timesum += controller->getTimespan(i);
        if(playSpeed > 0){
           ++i;
        } else {
           --i;
        }
    }
}

void PlayTool::updateSlider()
{
    emit positionChanged(timesum);
}

void PlayTool::playFastForward(float f){
    playSpeed = f;

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

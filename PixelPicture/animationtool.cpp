#include "animationtool.h"
#include <QElapsedTimer>

AnimationTool::AnimationTool(PixelScene *pscene)
{
    scene = pscene;
    connect(&timer, &QTimer::timeout, this, &AnimationTool::updateScene);
    timer.setSingleShot(true);
}

AnimationTool::~AnimationTool()
{

}

void AnimationTool::play()
{
    i = 0;
    updateScene();
}

void AnimationTool::updateScene()
{
    if (i < scene->frames.size())
    {
        scene->activeCanvas = scene->frames[i]->canvas;
        scene->updateScene();
        timer.start(scene->frames[i]->timespan);
        ++i;
    }
}

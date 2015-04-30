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

    /*
    QElapsedTimer timer;
    timer.start();
    int sum = 0;
    for(int i = 0; i<scene->frames.size();i++)
    {
        sum += scene->frames[i]->timespan;
        scene->activeCanvas = scene->frames[i]->canvas;
        scene->updateScene();
        while(timer.elapsed()<sum)
        {

        }
        //QTimer::singleShot(scene->frames[i]->timespan,SLOT(updateScene()));
    }
    */
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

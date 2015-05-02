#include "animation.h"

Animation::Animation(PixelScene *s)
{
    Frame* f = new Frame();
    frames.append(f);

    scene = s;
}

Animation::~Animation()
{
    while (!frames.isEmpty())
        delete frames.takeFirst();
}

void Animation::addFrame(int position)
{
    Frame* f = new Frame();
    frames.insert(position, f);

    scene->updateScene();
}


#ifndef ANIMATION_H
#define ANIMATION_H

#include "frame.h"
#include "pixelscene.h"

class Animation
{
public:
    Animation(PixelScene* s);
    ~Animation();

    void addFrame(int position);

    QList<Frame*> frames;
    float timesum = 0;
    PixelScene* scene;
};

#endif // ANIMATION_H

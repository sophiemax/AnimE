#ifndef ANIMATIONTOOL_H
#define ANIMATIONTOOL_H

#include "pixelscene.h"
#include <QTimer>

class AnimationTool : public QObject
{
    Q_OBJECT

public:
    AnimationTool(PixelScene *pscene);

    ~AnimationTool();

    void play();

public slots:
    void updateScene();

private:
    PixelScene *scene;
    int i = 0;
    QTimer timer;
};

#endif // ANIMATIONTOOL_H

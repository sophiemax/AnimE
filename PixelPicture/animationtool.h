#ifndef ANIMATIONTOOL_H
#define ANIMATIONTOOL_H

#include "controller.h"
#include <QTimer>

class AnimationTool : public QObject
{
    Q_OBJECT

public:
    AnimationTool(Controller *c);

    ~AnimationTool();

    void play();

public slots:
    void updateScene();
    void updateSlider();

signals:
    void positionChanged(int position);
private:
    Controller *controller;
    int i = 0;
    float timesum = 0.0;
    QTimer timer;
};

#endif // ANIMATIONTOOL_H

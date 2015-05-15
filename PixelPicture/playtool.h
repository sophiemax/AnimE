#ifndef PLAYTOOL_H
#define PLAYTOOL_H

#include "controller.h"
#include <QTimer>

class PlayTool : public QObject
{
    Q_OBJECT

public:
    PlayTool(Controller *c);

    ~PlayTool();

    void play();

public slots:
    void updateScene();
    void updateSlider();

signals:
    void positionChanged(int position);
private:
    //módosítások lekommunikálásához
    Controller *controller;
    //frame számláló
    int i = 0;
    //eltelt idő számláló
    float timesum = 0.0;
    //időzítést megvalósító timer
    QTimer timer;
};

#endif // PLAYTOOL_H

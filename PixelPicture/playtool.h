#ifndef PLAYTOOL_H
#define PLAYTOOL_H

#include "controller.h"
#include <QTimer>

class PlayTool : public QObject
{
    Q_OBJECT

public:
    //a playtool létrehozása a megfelelő controller pointerrel
    PlayTool(Controller *c);
    ~PlayTool();

    //lejátszás elindítását szolgáló függvény
    void play();

    //lejátszás megállítását szolgáló függvény
    void Pause();

    //lejátszás leállítását szolgáló függvény
    void Stop();

    //lejátszás sebességét beállítja
    void playFastForward(float f);
public slots:
    //a kijelző frissítését szolgáló slot
    void updateScene();
    //a slider frissítésére szolgáló slot
    void updateSlider();

signals:
    //a slider számára singal, ha a pozíció változott
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
    //a lejátszás sebességét állítja, ha negatív, akkor visszafelé játszuk le az animációt
    float playSpeed = 1.0;
};

#endif // PLAYTOOL_H

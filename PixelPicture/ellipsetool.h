#ifndef ELLIPSETOOL_H
#define ELLIPSETOOL_H

#include "painttool.h"

class EllipseTool : public PaintTool
{
    Q_OBJECT

public:
    EllipseTool(QObject *parent);
    ~EllipseTool();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
private:
    //egy ellipszist rajzol, az előzetes beállítás szerint ez lehet pontos, vagy színezhető
    void drawPixelEllipse();
    //pontos ellipszis rajzolása, ahol az elsődleges szempont a geometria követése
    void drawAccurateEllipse();
    //színezhető ellipszis rajzolása, ahol az elsődleges szempont folytonos alakzat rajzolása
    void drawFillableEllipse();
};

#endif // ELLIPSETOOL_H

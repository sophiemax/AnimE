#ifndef PAINTTOOL_H
#define PAINTTOOL_H

#include <QtGui>
#include <QtCore>

#include <QGraphicsSceneMouseEvent>
#include "controller.h"

class Controller;

class PaintTool : public QObject
{
    Q_OBJECT

public:
    PaintTool(QObject *parent = 0);
    ~PaintTool();
    //egérműveletek lekezelését szolgáló függvények
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) = 0;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) = 0;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) = 0;
    virtual void toggleFilled(bool state);

    void setController(Controller *c);

protected:
    //az egérművelet kezdő és végpontja
    QPointF startPoint, endPoint;
    //módosítások lekommunikálásához
    Controller *controller;
    //be van-e nyomva a fillable RadioButton
    bool fillable;
};

#endif // PAINTTOOL_H

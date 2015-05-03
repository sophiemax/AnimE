#ifndef TOOL_H
#define TOOL_H

#include <QtGui>
#include <QtCore>

#include <QGraphicsSceneMouseEvent>
#include "controller.h"

class Controller;

class Tool : public QObject
{
    Q_OBJECT

public:
    Tool(QObject *parent = 0);
    ~Tool();
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) = 0;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) = 0;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) = 0;

    void setController(Controller *c);

protected:
    QPointF startPoint, endPoint;
    Controller *controller;
};

#endif // TOOL_H

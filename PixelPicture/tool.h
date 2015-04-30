#ifndef TOOL_H
#define TOOL_H

#include <QtGui>
#include <QtCore>
#include "pixelscene.h"

class PixelScene;

class Tool : public QObject
{
    Q_OBJECT

public:
    Tool(QObject *parent = 0);
    ~Tool();
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event, PixelScene *scene) = 0;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event, PixelScene *scene) = 0;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event, PixelScene *scene) = 0;
protected:
    QPointF startPoint, endPoint;
};

#endif // TOOL_H

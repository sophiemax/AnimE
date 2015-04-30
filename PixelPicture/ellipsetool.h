#ifndef ELLIPSETOOL_H
#define ELLIPSETOOL_H

#include "tool.h"

class EllipseTool : public Tool
{
    Q_OBJECT

public:
    EllipseTool(QObject *parent);
    ~EllipseTool();
    void mousePressEvent(QGraphicsSceneMouseEvent *event, PixelScene *scene);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event, PixelScene *scene);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event, PixelScene *scene);
private:
    void drawPixelEllipse(PixelScene *scene);
};

#endif // ELLIPSETOOL_H

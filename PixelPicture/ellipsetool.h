#ifndef ELLIPSETOOL_H
#define ELLIPSETOOL_H

#include "tool.h"

class EllipseTool : public Tool
{
    Q_OBJECT

public:
    EllipseTool(QObject *parent);
    ~EllipseTool();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
private:
    void drawPixelEllipse();
    void drawAccurateEllipse();
    void drawFillableEllipse();
};

#endif // ELLIPSETOOL_H

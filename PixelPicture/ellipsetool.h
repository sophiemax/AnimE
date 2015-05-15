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
    void drawPixelEllipse();
    void drawAccurateEllipse();
    void drawFillableEllipse();
};

#endif // ELLIPSETOOL_H

#ifndef ERASERTOOL_H
#define ERASERTOOL_H

#include "painttool.h"

class EraserTool : public PaintTool
{
    Q_OBJECT

public:
    EraserTool(QObject *parent);
    ~EraserTool();

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
private:
    void eraserMouseEvent();
};

#endif // ERASERTOOL_H

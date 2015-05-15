#ifndef PENTOOL_H
#define PENTOOL_H

#include "painttool.h"

class PenTool : public PaintTool
{
    Q_OBJECT

public:
    PenTool(QObject *parent);
    ~PenTool();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
private:
    void penMouseEvent();
};

#endif // PENTOOL_H

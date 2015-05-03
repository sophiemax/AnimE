#ifndef PENTOOL_H
#define PENTOOL_H

#include "tool.h"

class PenTool : public Tool
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

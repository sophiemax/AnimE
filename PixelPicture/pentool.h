#ifndef PENTOOL_H
#define PENTOOL_H

#include "tool.h"

class PenTool : public Tool
{
    Q_OBJECT

public:
    PenTool(QObject *parent);
    ~PenTool();
    void mousePressEvent(QGraphicsSceneMouseEvent *event, PixelScene *scene);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event, PixelScene *scene);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event, PixelScene *scene);
private:
    void penMouseEvent(PixelScene* scene);
};

#endif // PENTOOL_H

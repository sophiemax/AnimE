#ifndef ERASERTOOL_H
#define ERASERTOOL_H

#include "tool.h"

class EraserTool : public Tool
{
    Q_OBJECT

public:
    EraserTool(QObject *parent);
    ~EraserTool();

    void mousePressEvent(QGraphicsSceneMouseEvent *event, PixelScene *scene);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event, PixelScene *scene);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event, PixelScene *scene);
private:
    void eraserMouseEvent(PixelScene* scene);
};

#endif // ERASERTOOL_H

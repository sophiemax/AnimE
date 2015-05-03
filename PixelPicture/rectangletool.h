#ifndef RECTANGLETOOL_H
#define RECTANGLETOOL_H

#include "tool.h"

class RectangleTool : public Tool
{
public:

    Q_OBJECT

public:
    RectangleTool(QObject *parent);
    ~RectangleTool();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
private:
    void drawPixelRectangle();
};

#endif // RECTANGLETOOL_H

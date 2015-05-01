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
    void mousePressEvent(QGraphicsSceneMouseEvent *event, PixelScene *scene);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event, PixelScene *scene);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event, PixelScene *scene);
private:
    void drawPixelRectangle(PixelScene *scene);
};

#endif // RECTANGLETOOL_H

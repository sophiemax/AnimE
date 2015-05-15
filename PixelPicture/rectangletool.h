#ifndef RECTANGLETOOL_H
#define RECTANGLETOOL_H

#include "painttool.h"

class RectangleTool : public PaintTool
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
    //téglalap rajzolását megvalósító függvény
    void drawPixelRectangle();
};

#endif // RECTANGLETOOL_H

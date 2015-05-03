#ifndef FILLTOOL_H
#define FILLTOOL_H

#include "tool.h"

class FillTool : public Tool
{
    Q_OBJECT

public:
    FillTool(QObject *parent);
    ~FillTool();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    QColor color;

private:
    void fill(int index);

    Pixel *start;
};

#endif // FILLTOOL_H

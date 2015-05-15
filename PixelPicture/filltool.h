#ifndef FILLTOOL_H
#define FILLTOOL_H

#include "painttool.h"

class FillTool : public PaintTool
{
    Q_OBJECT

public:
    FillTool(QObject *parent);
    ~FillTool();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    //a színezést végző függvény
    void fill(int index);

    //kezdőszín eltárolásához
    QColor color;
};

#endif // FILLTOOL_H

#ifndef FILLTOOL_H
#define FILLTOOL_H

#include "tool.h"

class FillTool : public Tool
{
    Q_OBJECT

public:
    FillTool(QObject *parent);
    ~FillTool();
    void mousePressEvent(QGraphicsSceneMouseEvent *event, PixelScene *scene);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event, PixelScene *scene);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event, PixelScene *scene);

    QColor color;

private:
    void fill(PixelScene *scene, Pixel *pixel);

    Pixel *start;
};

#endif // FILLTOOL_H

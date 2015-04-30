#ifndef LINETOOL_H
#define LINETOOL_H

#include "tool.h"

class LineTool : public Tool
{
    Q_OBJECT

public:
    LineTool(QObject *parent);
    ~LineTool();
    void mousePressEvent(QGraphicsSceneMouseEvent *event, PixelScene *scene);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event, PixelScene *scene);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event, PixelScene *scene);
private:
    void drawPixelLine(PixelScene* scene);
};

#endif // LINETOOL_H

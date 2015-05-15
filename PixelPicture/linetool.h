#ifndef LINETOOL_H
#define LINETOOL_H

#include "painttool.h"

class LineTool : public PaintTool
{
    Q_OBJECT

public:
    LineTool(QObject *parent);
    ~LineTool();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
private:
    //A beállítás alapján kirajzol egy pontos, vagy egy folytonos vonalat
    void drawPixelLine();
    //a vonal kirajzolásakor a geometriai pontosság elsődleges
    void drawAccuratePixelLine();
    //a vonal kirajzolásakor a folytonosság az elsődleges
    void drawFillablePixelLine();
};

#endif // LINETOOL_H

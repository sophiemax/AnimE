#include "linetool.h"

LineTool::LineTool(QObject *parent) :
    Tool(parent)
{

}

LineTool::~LineTool()
{

}

void LineTool::mousePressEvent(QGraphicsSceneMouseEvent *event, PixelScene *scene)
{
    Q_UNUSED(scene)
    startPoint = event->scenePos();
}

void LineTool::mouseMoveEvent(QGraphicsSceneMouseEvent *event, PixelScene *scene)
{
    Q_UNUSED(scene)
    endPoint = event->scenePos();
}

void LineTool::mouseReleaseEvent(QGraphicsSceneMouseEvent *event, PixelScene *scene)
{
    endPoint = event->scenePos();
    drawPixelLine(scene);
}

void LineTool::drawPixelLine(PixelScene *scene)
{

}


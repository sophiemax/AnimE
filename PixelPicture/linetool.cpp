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
    //Getting nearest Pixels:
    Pixel *begin = scene->nearestPixel(startPoint.x(), startPoint.y());
    Pixel *end = scene->nearestPixel(endPoint.x(), endPoint.y());

    float startX = begin->rect.center().x();
    float startY = begin->rect.center().y();
    float endX = end->rect.center().x();
    float endY = end->rect.center().y();

    float m = (endX-startX)/(endY-startY);



}


#include "rectangletool.h"

RectangleTool::RectangleTool(QObject *parent) :
    Tool(parent)
{

}

RectangleTool::~RectangleTool()
{

}

void RectangleTool::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    startPoint = event->scenePos();
}

void RectangleTool::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    endPoint = event->scenePos();
}

void RectangleTool::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    endPoint = event->scenePos();
    drawPixelRectangle();
}

void RectangleTool::drawPixelRectangle()
{
    if(startPoint!=endPoint)
    {
        QRect start = controller->nearestPixelRect(startPoint.x(),startPoint.y());
        QRect end = controller->nearestPixelRect(endPoint.x(), endPoint.y());

        int a = start.center().x() - end.center().x();
        int b = start.center().y() - end.center().y();

        int directionX = a > 0 ? 1 : -1;
        int directionY = b > 0 ? 1 : -1;

        for(int i = 0; i < abs(a); i+=controller->getPixelSize())
        {
            float x = start.center().x() + i * directionX;
            float y1 = start.center().y();
            float y2 = end.center().y();

            int index_starty = controller->containsPoint(x,y1);
            if(index_starty!=-1)
            {
                int index_endy = controller->containsPoint(x,y2);

                controller->setColorofPixel(index_starty);
                controller->setColorofPixel(index_endy);
            }
        }

        for(int i = 0; i < b; i+=controller->getPixelSize())
        {
            float y = start.center().y() + i * directionY;
            float x1 = start.center().x();
            float x2 = end.center().x();

            int index_startx = controller->containsPoint(x1,y);
            if(index_startx!=-1)
            {
                int index_endx = controller->containsPoint(x2,y);

                controller->setColorofPixel(index_startx);
                controller->setColorofPixel(index_endx);
            }
        }

        int endindex = controller->containsPoint(end.center().x(),end.center().y());
        controller->setColorofPixel(endindex);
    }
}


#include "ellipsetool.h"

#include <iostream>

EllipseTool::EllipseTool(QObject *parent) :
    Tool(parent)
{

}

EllipseTool::~EllipseTool()
{

}

void EllipseTool::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    startPoint = event->scenePos();
}

void EllipseTool::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    endPoint = event->scenePos();
}

void EllipseTool::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    endPoint = event->scenePos();
    drawPixelEllipse();
}

void EllipseTool::drawPixelEllipse()
{
    if(startPoint!=endPoint)
    {
        //A felhasználó által adott alapokat pixelekre kerekítjük:
        // Adatok:
        float centerX = (endPoint.x()+startPoint.x())/2.0;
        float centerY = (endPoint.y()+startPoint.y())/2.0;
        float a = fabs(endPoint.x()-startPoint.x())/2.0;
        float b = fabs(endPoint.y()-startPoint.y())/2.0;

        //legközelebbi pixel keresése:
        QRect bottom = controller->nearestPixelRect(centerX, centerY + b);
        QRect top = controller->nearestPixelRect(centerX, centerY - b);
        QRect left = controller->nearestPixelRect(centerX - a, centerY);
        QRect right = controller->nearestPixelRect(centerX + a, centerY);

        //miután megvannak a pixelek, újra ki kell számítani az ellipszis adatait.
        float ellipseLeftBound = left.center().x();
        float ellipseRightBound = right.center().x();
        float ellipseTopBound = top.center().y();
        float ellipseBottomBound =  bottom.center().y();

        //Konkrét paraméterek, a koordinátákból számolva:
        float ellipseCenterX = (ellipseLeftBound + ellipseRightBound)/2.0;
        float ellipseCenterY = (ellipseTopBound + ellipseBottomBound)/2.0;
        float ellipseA = fabs(ellipseLeftBound - ellipseRightBound)/2.0;
        float ellipseB = fabs(ellipseTopBound - ellipseBottomBound)/2.0;

        //A precision megadja, hogy milyen sűrű legyen az iteráció kirajzoláskor.
        float precision = M_PI * 2.0 / 360;

        //a precisionban megadott Radiánonként körberajzoljuk az ellipszist.
        for(float i = 0; i<M_PI*2; i+=precision)
        {
            float x,y;
            x = ellipseCenterX + ellipseA * cosf(i);
            y = ellipseCenterY + ellipseB * sinf(i);

            int index = controller->containsPoint(x,y);
            if(index != -1)
                controller->setColorofPixel(index);
        }
    }
}

#include "ellipsetool.h"

#include <iostream>

EllipseTool::EllipseTool(QObject *parent) :
    PaintTool(parent)
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
    if(startPoint!=endPoint)
    {
        if(!fillable)
        {
        drawPixelEllipse();
        }
        else
        {
            drawFillableEllipse();
        }
    }
}

void EllipseTool::drawPixelEllipse()
{
    //A beállítás szerint pontos, vagy kitölthető ellipszist rajzolunk
    //drawFillableEllipse();
    drawAccurateEllipse();
}

void EllipseTool::drawAccurateEllipse()
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

void EllipseTool::drawFillableEllipse()
{
    //A felhasználó által adott alapokat pixelekre kerekítjük:
    QRect startPixel = controller->nearestPixelRect(startPoint.x(), startPoint.y());
    QRect endPixel = controller->nearestPixelRect(endPoint.x(), endPoint.y());
    // Adatok:
    float centerX = (endPixel.x()+startPixel.x())/2.0;
    float centerY = (endPixel.y()+startPixel.y())/2.0;
    float a = abs(endPixel.x()-startPixel.x())/2.0;
    float b = abs(endPixel.y()-startPixel.y())/2.0;

    //legközelebbi pixel keresése:
    QRect bottom = controller->nearestPixelRect(centerX, centerY + b);
    QRect top = controller->nearestPixelRect(centerX, centerY - b);
    QRect left = controller->nearestPixelRect(centerX - a, centerY);
    QRect right = controller->nearestPixelRect(centerX + a, centerY);

    //miután megvannak a pixelek, újra kell számolni a pixel adatait.
    int bottomIndex = controller->containsPoint(bottom.x(),bottom.y());
    int topIndex = controller->containsPoint(top.x(),top.y());
    int leftIndex = controller->containsPoint(left.x(),left.y());
    int rightIndex = controller->containsPoint(right.x(),right.y());

    //Ezek után csak a pixelindexeket használva rajzolunk ki egy ellipszist (nem figyelve az ablakok közti résekre)
    int ellipseA = abs(rightIndex - leftIndex)/2;
    int ellipseB = abs(topIndex - bottomIndex) / (controller->originalnumberofcolumns() * 2);
    int startIndex = topIndex - ellipseA;

    //A precision megadja, hogy milyen sűrű legyen az iteráció kirajzoláskor.
    float precision = M_PI * 2.0 / 360;

    //a precisionban megadott radiánonként körberajzoljuk az ellipszist.
    for(float i = 0; i<M_PI*2; i+=precision)
    {
        int x,y;
        x = ellipseA + ellipseA * cosf(i);
        y = ellipseB + ellipseB * sinf(i);

        //A pixelsceneben lévő index kiszámolása.
        int pixelIndex = startIndex + x + y*(controller->originalnumberofcolumns());
        //centerindex = startIndex + ellipseA + ellipseB*oszlopszám

        int index = pixelIndex;//controller->containsPoint(x,y);
        if(index != -1)
            controller->setColorofPixel(index);
    }
}

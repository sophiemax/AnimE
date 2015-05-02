#include "ellipsetool.h"

#include <iostream>

EllipseTool::EllipseTool(QObject *parent) :
    Tool(parent)
{

}

EllipseTool::~EllipseTool()
{

}

void EllipseTool::mousePressEvent(QGraphicsSceneMouseEvent *event, PixelScene *scene)
{
    Q_UNUSED(scene)
    startPoint = event->scenePos();
}

void EllipseTool::mouseMoveEvent(QGraphicsSceneMouseEvent *event, PixelScene *scene)
{
    Q_UNUSED(scene)
    endPoint = event->scenePos();
}

void EllipseTool::mouseReleaseEvent(QGraphicsSceneMouseEvent *event, PixelScene *scene)
{
    endPoint = event->scenePos();
    drawPixelEllipse(scene);
}

void EllipseTool::drawPixelEllipse(PixelScene *scene)
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
        Pixel *bottom = scene->nearestPixel(centerX, centerY + b);
        Pixel *top = scene->nearestPixel(centerX, centerY - b);
        Pixel *left = scene->nearestPixel(centerX - a, centerY);
        Pixel *right = scene->nearestPixel(centerX + a, centerY);

        //miután megvannak a pixelek, újra ki kell számítani az ellipszis adatait.
        float ellipseLeftBound = left->rect.center().x();
        float ellipseRightBound = right->rect.center().x();
        float ellipseTopBound = top->rect.center().y();
        float ellipseBottomBound =  bottom->rect.center().y();

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

            Pixel *p = scene->containsPoint(x,y);
            if(p!=NULL)
            {
                int index = p->index;
                if(scene->windowToggled)
                {
                    p->window->setWindowColor(scene->primaryColor);
                    p->window->updateWindow();
                }
                else
                {
                    scene->activeCanvas->activeLayer->pixels[index]->clear = false;
                    scene->activeCanvas->activeLayer->pixels[index]->color = scene->primaryColor;
                    scene->updateCombinedLayer(index);
                    scene->updatePixel(index);
                }
            }
        }
    }
}

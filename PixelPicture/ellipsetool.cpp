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
        float centerX = (endPoint.x()+startPoint.x())/2.0;
        float centerY = (endPoint.y()+startPoint.y())/2.0;
        float a = fabs(endPoint.x()-startPoint.x())/2.0;
        float b = fabs(endPoint.y()-startPoint.y())/2.0;

        float precision = M_PI * 2.0 / 180;

        Pixel *bottom = scene->containsPoint(centerX, centerY + b);
        Pixel *top    = scene->containsPoint(centerX, centerY - b);
        Pixel *left   = scene->containsPoint(centerX - a, centerY);
        Pixel *right  = scene->containsPoint(centerX + a, centerY);

        float bbottom = b, btop = b, aleft = a, aright = a;

        if(bottom == NULL)
        {
            bottom = scene->nearestPixel(centerX, centerY + b);
            bbottom = bottom->rect.center().y() - centerY;
        }

        if(top == NULL)
        {
            top = scene->nearestPixel(centerX, centerY - b);
            btop = centerY - top->rect.center().y();
        }

        if(left == NULL)
        {
            left = scene->nearestPixel(centerX - a, centerY);
            aleft = centerX - left->rect.center().x();
        }

        if(right == NULL)
        {
            right = scene->nearestPixel(centerX + a, centerY);
            aright = right->rect.center().x() - centerX;
        }

        QTextStream(stdout) << a << endl;
        QTextStream(stdout) << aright << endl;

        for(float i = 0; i<M_PI*2; i+=precision)
        {
            float x,y;
            if(i<M_PI/2 || i>3*M_PI/2)
                x = centerX + aleft * cosf(i);
            else
                x = centerX + aright * cosf(i);

            if(i<M_PI)
                y = centerY + btop * sinf(i);
            else
                y = centerY + bbottom * sinf(i);

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

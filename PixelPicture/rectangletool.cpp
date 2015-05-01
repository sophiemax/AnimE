#include "rectangletool.h"

RectangleTool::RectangleTool(QObject *parent) :
    Tool(parent)
{

}

RectangleTool::~RectangleTool()
{

}

void RectangleTool::mousePressEvent(QGraphicsSceneMouseEvent *event, PixelScene *scene)
{
    Q_UNUSED(scene)
    startPoint = event->scenePos();
}

void RectangleTool::mouseMoveEvent(QGraphicsSceneMouseEvent *event, PixelScene *scene)
{
    Q_UNUSED(scene)
    endPoint = event->scenePos();
}

void RectangleTool::mouseReleaseEvent(QGraphicsSceneMouseEvent *event, PixelScene *scene)
{
    endPoint = event->scenePos();
    drawPixelRectangle(scene);
}

void RectangleTool::drawPixelRectangle(PixelScene *scene)
{
    if(startPoint!=endPoint)
    {
        Pixel *start = scene->nearestPixel(startPoint.x(),startPoint.y());
        Pixel *end = scene->nearestPixel(endPoint.x(), endPoint.y());

        float a = fabs(start->rect.center().x() - end->rect.center().x());
        float b = fabs(start->rect.center().y() - end->rect.center().y());

        int directionX = a > 0 ? 1 : -1;
        int directionY = b > 0 ? 1 : -1;

        for(int i = 0; i < a; i+=scene->pixelSize)
        {
            float x = start->rect.center().x() + i * directionX;
            float y1 = start->rect.center().y();
            float y2 = end->rect.center().y();

            Pixel *p_starty = scene->containsPoint(x,y1);
            if(p_starty!=NULL)
            {
                Pixel *p_endy = scene->containsPoint(x,y2);
                int index1 = p_starty->index;
                int index2 = p_endy->index;
                if(scene->windowToggled)
                {
                    p_starty->window->setWindowColor(scene->primaryColor);
                    p_starty->window->updateWindow();

                    p_endy->window->setWindowColor(scene->primaryColor);
                    p_endy->window->updateWindow();
                }
                else
                {
                    scene->activeCanvas->activeLayer->pixels[index1]->clear = false;
                    scene->activeCanvas->activeLayer->pixels[index1]->color = scene->primaryColor;
                    scene->updateCombinedLayer(index1);
                    scene->updatePixel(index1);

                    scene->activeCanvas->activeLayer->pixels[index2]->clear = false;
                    scene->activeCanvas->activeLayer->pixels[index2]->color = scene->primaryColor;
                    scene->updateCombinedLayer(index2);
                    scene->updatePixel(index2);
                }
            }
        }

        for(int i = 0; i < b; i+=scene->pixelSize)
        {
            float y = start->rect.center().y() + i * directionY;
            float x1 = start->rect.center().x();
            float x2 = end->rect.center().x();

            Pixel *p_startx = scene->containsPoint(x1,y);
            if(p_startx!=NULL)
            {
                Pixel *p_endx = scene->containsPoint(x2,y);
                int index1 = p_startx->index;
                int index2 = p_endx->index;
                if(scene->windowToggled)
                {
                    p_startx->window->setWindowColor(scene->primaryColor);
                    p_startx->window->updateWindow();

                    p_endx->window->setWindowColor(scene->primaryColor);
                    p_endx->window->updateWindow();
                }
                else
                {
                    scene->activeCanvas->activeLayer->pixels[index1]->clear = false;
                    scene->activeCanvas->activeLayer->pixels[index1]->color = scene->primaryColor;
                    scene->updateCombinedLayer(index1);
                    scene->updatePixel(index1);

                    scene->activeCanvas->activeLayer->pixels[index2]->clear = false;
                    scene->activeCanvas->activeLayer->pixels[index2]->color = scene->primaryColor;
                    scene->updateCombinedLayer(index2);
                    scene->updatePixel(index2);
                }
            }
        }

        if(scene->windowToggled)
        {
            end->window->setWindowColor(scene->primaryColor);
            end->window->updateWindow();
        }
        else
        {
            int index = end->index;
            scene->activeCanvas->activeLayer->pixels[index]->clear = false;
            scene->activeCanvas->activeLayer->pixels[index]->color = scene->primaryColor;
            scene->updateCombinedLayer(index);
            scene->updatePixel(index);
        }
    }
}


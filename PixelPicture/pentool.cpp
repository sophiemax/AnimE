#include "pentool.h"

PenTool::PenTool(QObject *parent) :
    Tool(parent)
{

}

PenTool::~PenTool()
{

}

void PenTool::mousePressEvent(QGraphicsSceneMouseEvent *event, PixelScene *scene)
{
    Q_UNUSED(event)
    penMouseEvent(scene);
}

void PenTool::mouseMoveEvent(QGraphicsSceneMouseEvent *event, PixelScene *scene)
{
    Q_UNUSED(event)
    penMouseEvent(scene);
}

void PenTool::mouseReleaseEvent(QGraphicsSceneMouseEvent *event, PixelScene *scene)
{
    Q_UNUSED(event)
    penMouseEvent(scene);
}

void PenTool::penMouseEvent(PixelScene *scene)
{
    Pixel* p = scene->pixelUnderMouse();
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

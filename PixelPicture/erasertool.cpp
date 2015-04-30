#include "erasertool.h"

EraserTool::EraserTool(QObject *parent) :
    Tool(parent)
{

}

EraserTool::~EraserTool()
{

}

void EraserTool::mousePressEvent(QGraphicsSceneMouseEvent *event, PixelScene *scene)
{
    Q_UNUSED(event)
    eraserMouseEvent(scene);
}

void EraserTool::mouseMoveEvent(QGraphicsSceneMouseEvent *event, PixelScene *scene)
{
    Q_UNUSED(event)
    eraserMouseEvent(scene);
}

void EraserTool::mouseReleaseEvent(QGraphicsSceneMouseEvent *event, PixelScene *scene)
{
    Q_UNUSED(event)
    eraserMouseEvent(scene);
}

void EraserTool::eraserMouseEvent(PixelScene *scene)
{
    Pixel* p = scene->pixelUnderMouse();
    if(p!=NULL)
    {
        int index = p->index;
        if(scene->windowToggled)
        {
            p->window->clearWindow();
            p->window->updateWindow();
        }
        else
        {
            scene->activeCanvas->activeLayer->pixels[index]->clear = true;
            scene->updateCombinedLayer(index);
            scene->updatePixel(index);
        }
    }
}

#include "pentool.h"

PenTool::PenTool(QObject *parent) :
    Tool(parent)
{

}

PenTool::~PenTool()
{

}

void PenTool::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    penMouseEvent();
}

void PenTool::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    penMouseEvent();
}

void PenTool::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    penMouseEvent();
}

void PenTool::penMouseEvent()
{
    int index = controller->pixelUnderMouse();
    if(index != -1)
        controller->setColorofPixel(index);
}

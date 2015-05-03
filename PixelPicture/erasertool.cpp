#include "erasertool.h"

EraserTool::EraserTool(QObject *parent) :
    Tool(parent)
{

}

EraserTool::~EraserTool()
{

}

void EraserTool::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    eraserMouseEvent();
}

void EraserTool::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    eraserMouseEvent();
}

void EraserTool::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    eraserMouseEvent();
}

void EraserTool::eraserMouseEvent()
{
    int index = controller->pixelUnderMouse();
    if(index != -1)
        controller->clearPixel(index);
}

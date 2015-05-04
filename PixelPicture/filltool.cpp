#include "filltool.h"

FillTool::FillTool(QObject *parent) :
    Tool(parent)
{

}

FillTool::~FillTool()
{

}

void FillTool::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    startPoint = event->scenePos();
    int index = controller->nearestPixel(startPoint.x(),startPoint.y());
    color = controller->getColorofPixel(index);
    fill(index);
}

void FillTool::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
}

void FillTool::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
}

void FillTool::fill(int index)
{
    int pixelsinarow = controller->pixelsinaRow();
    int numberofPixels = controller->numberofPixels();

    controller->setColorofPixelFill(index);

    //jobbra hív, ha nem a szélén van
    if(!((index+1) % pixelsinarow == 0) && controller->getColorofPixel(index+1) == color)
        fill(index+1);

    //balra hív, ha nem a szélén van
    if(!(index % pixelsinarow == 0) && controller->getColorofPixel(index-1) == color)
        fill(index-1);

    //fel hív, ha nem a legfelső sor
    if(index >= pixelsinarow && controller->getColorofPixel(index - pixelsinarow) == color)
        fill(index - pixelsinarow);

    //le hív, ha nem a legalsó sor
    if(index < (numberofPixels - pixelsinarow) && controller->getColorofPixel(index + pixelsinarow) == color)
        fill(index + pixelsinarow);

}


#include "filltool.h"

FillTool::FillTool(QObject *parent) :
    Tool(parent)
{

}

FillTool::~FillTool()
{

}

void FillTool::mousePressEvent(QGraphicsSceneMouseEvent *event, PixelScene *scene)
{
    startPoint = event->scenePos();
    Pixel *start = scene->nearestPixel(startPoint.x(),startPoint.y());
    color = start->brush->color();
    fill(scene,start);
}

void FillTool::mouseMoveEvent(QGraphicsSceneMouseEvent *event, PixelScene *scene)
{
    Q_UNUSED(event)
    Q_UNUSED(scene)
}

void FillTool::mouseReleaseEvent(QGraphicsSceneMouseEvent *event, PixelScene *scene)
{
    Q_UNUSED(event)
    Q_UNUSED(scene)
}

void FillTool::fill(PixelScene *scene, Pixel *pixel)
{
    int pixelsinarow = scene->pixelsinaRow();

    int index = pixel->index;

    scene->activeCanvas->activeLayer->pixels[index]->clear = false;
    scene->activeCanvas->activeLayer->pixels[index]->color = scene->primaryColor;
    scene->updateCombinedLayer(index);
    scene->updatePixel(index);

    //jobbra hív, ha nem a szélén van
    if(!((index+1) % pixelsinarow == 0) && scene->pixels[index+1]->brush->color() == color)
        fill(scene, scene->pixels[index+1]);
    //balra hív, ha nem a szélén van
    if(!(index % pixelsinarow == 0) && scene->pixels[index-1]->brush->color() == color)
        fill(scene, scene->pixels[index-1]);
    //fel hív, ha nem a legfelső sor
    if(index >= pixelsinarow && scene->pixels[index - pixelsinarow]->brush->color() == color)
        fill(scene, scene->pixels[index - pixelsinarow]);
    //le hív, ha nem a legalsó sor
    if(index < (scene->pixels.size() - pixelsinarow) && scene->pixels[index + pixelsinarow]->brush->color() == color)
        fill(scene, scene->pixels[index + pixelsinarow]);
}


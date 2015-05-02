#include "linetool.h"

LineTool::LineTool(QObject *parent) :
    Tool(parent)
{

}

LineTool::~LineTool()
{

}

void LineTool::mousePressEvent(QGraphicsSceneMouseEvent *event, PixelScene *scene)
{
    Q_UNUSED(scene)
    startPoint = event->scenePos();
}

void LineTool::mouseMoveEvent(QGraphicsSceneMouseEvent *event, PixelScene *scene)
{
    Q_UNUSED(scene)
    endPoint = event->scenePos();
}

void LineTool::mouseReleaseEvent(QGraphicsSceneMouseEvent *event, PixelScene *scene)
{
    endPoint = event->scenePos();
    drawPixelLine(scene);
}

void LineTool::drawPixelLine(PixelScene *scene)
{
    //Getting nearest Pixels:
    Pixel *begin = scene->nearestPixel(startPoint.x(), startPoint.y());
    Pixel *end = scene->nearestPixel(endPoint.x(), endPoint.y());

    //Új kezdő és végpontok koordinátái.
    float startX = begin->rect.center().x();
    float startY = begin->rect.center().y();
    float endX = end->rect.center().x();
    float endY = end->rect.center().y();

    //Meredekség
    float deltaX = (endX-startX);
    float deltaY = (endY-startY);
    float m = 0.0;
    if(deltaX != 0.0){
        m = deltaY/deltaX;
    }
    float length = sqrtf(deltaX*deltaX + deltaY*deltaY);


    //Az iterálás során egy iterációval megtett távolság:
    float precision = scene->pixelSize;
    float direction = (deltaX ==0) ? (deltaY/fabs(deltaY)) :(deltaX/fabs(deltaX));
    float distance = 0.0;

    //Amíg nem értünk el a végéig, precisionnal arrébb is beszínezzük a pixelt.
    while(fabs(distance) <= length)
    {
        float x, y;
        //Ki kell szűrni a függőleges vonalat, mert nem tudunk 0-val osztani.
        if(deltaX == 0.0)
        {
            x  = startX;
            y = startY + distance;
        }
        else
        {
            //Egyéb esetben a meredekség valós értéket ad, számolhatunk vele.
            x = startX + direction * sqrtf( distance*distance/(1 + m*m) );
            y = startY + (x - startX)*m;
        }

        //Kirajzolás.
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

        //A következő iterációra növeljük a megtett távolságot.
        distance += direction*precision;
    }
}

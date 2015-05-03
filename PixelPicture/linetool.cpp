#include "linetool.h"

LineTool::LineTool(QObject *parent) :
    Tool(parent)
{

}

LineTool::~LineTool()
{

}

void LineTool::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    startPoint = event->scenePos();
}

void LineTool::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    endPoint = event->scenePos();
}

void LineTool::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    endPoint = event->scenePos();
    drawPixelLine();
}

void LineTool::drawPixelLine()
{
    //Getting nearest Pixels:
    QRect begin = controller->nearestPixelRect(startPoint.x(), startPoint.y());
    QRect end = controller->nearestPixelRect(endPoint.x(), endPoint.y());

    //Új kezdő és végpontok koordinátái.
    float startX = begin.center().x();
    float startY = begin.center().y();
    float endX = end.center().x();
    float endY = end.center().y();

    //Meredekség
    float deltaX = (endX-startX);
    float deltaY = (endY-startY);
    float m = 0.0;
    if(deltaX != 0.0)
    {
        m = deltaY/deltaX;
    }
    float length = sqrtf(deltaX*deltaX + deltaY*deltaY);


    //Az iterálás során egy iterációval megtett távolság:
    float precision = controller->getPixelSize();
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
        int index = controller->containsPoint(x,y);
        if(index != -1)
            controller->setColorofPixel(index);

        //A következő iterációra növeljük a megtett távolságot.
        distance += direction*precision;
    }
}

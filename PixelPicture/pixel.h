#ifndef PIXEL_H
#define PIXEL_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QTextStream>
#include <QGraphicsScene>
class Window;

class Pixel : public QGraphicsItem
{
public:
    Pixel();

    //visszaadja a pixelt definiáló téglalapot
    QRectF boundingRect() const;
    //kirajzolja a megfelelő helyre a pixelt
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    ~Pixel();

    //kitöltéshez használt ecset
    QBrush* brush;
    //a pixel elhelyezkedése a scene-en
    QRect rect;
    //a pixelhez tartozó ablak
    Window* window;

    //a pixel indexe
    int index;
};

#endif // PIXEL_H

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

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    ~Pixel();

    QBrush* brush;
    QRectF rect;
    Window* window;

    int index;
};

#endif // PIXEL_H

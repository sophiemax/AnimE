#include "pixel.h"
#include <iostream>

Pixel::Pixel()
{
    brush = new QBrush();
    brush->setColor(Qt::black);
    brush->setStyle(Qt::SolidPattern);
}

QRectF Pixel::boundingRect() const
{
    return rect;
}

void Pixel::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter -> fillRect(rect,*brush);
}

Pixel::~Pixel()
{

}

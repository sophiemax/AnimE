#include "window.h"

Window::Window(PixelScene *s)
{
    scene = s;
}

Window::~Window()
{

}

void Window::setWindowColor(QColor color)
{
    foreach(int i, indexes)
    {
        scene->activeCanvas->activeLayer->pixels[i]->clear = false;
        scene->activeCanvas->activeLayer->pixels[i]->color = color;
    }
}

void Window::clearWindow()
{
    foreach(int i, indexes)
    {
        scene->activeCanvas->activeLayer->pixels[i]->clear = true;
    }
}

void Window::updateWindow()
{
    foreach(int i, indexes)
    {
        scene->updatePixel(i);
        scene->updateCombinedLayer(i);
    }
}

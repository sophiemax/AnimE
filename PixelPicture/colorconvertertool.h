#ifndef COLORCONVERTERTOOL_H
#define COLORCONVERTERTOOL_H

#include "controller.h"

class Controller;

class ColorConverterTool
{
public:
    ColorConverterTool(Controller* c, int p);
    ~ColorConverterTool();

    void inverz();
    void shiftright();
    void shiftleft();
    void blackandwhite();
    void greyscale();
    void colorfilter(QColor c);

private:
    //módosítások kommunikálásához
    Controller *controller;
    int numberofpixels;
};

#endif // COLORCONVERTERTOOL_H

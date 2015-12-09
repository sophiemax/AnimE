#include "colorconvertertool.h"

ColorConverterTool::ColorConverterTool(Controller *c, int p)
{
    controller = c;
    numberofpixels = p;
}

ColorConverterTool::~ColorConverterTool()
{

}

void ColorConverterTool::inverz()
{
    int red, green, blue;
    QColor newcolor, color;

    for(int i = 0; i < numberofpixels; i++)
    {
        color = controller->getColorofPixel(i);
        red = 255-color.red();
        green = 255-color.green();
        blue = 255-color.blue();

        newcolor = QColor(red,green,blue);

        //nincs lekezelve, ha a fekete az átlátszó szín
        controller->setColorofPixel(i, newcolor);
    }
}

void ColorConverterTool::shiftright()
{
    int red, green, blue;
    QColor newcolor, color;

    for(int i = 0; i < numberofpixels; i++)
    {
        color = controller->getColorofPixel(i);
        red = color.blue();
        green = color.red();
        blue = color.green();

        newcolor = QColor(red,green,blue);

        //nincs lekezelve, ha a fekete az átlátszó szín
        controller->setColorofPixel(i, newcolor);
    }
}

void ColorConverterTool::shiftleft()
{
    int red, green, blue;
    QColor newcolor, color;

    for(int i = 0; i < numberofpixels; i++)
    {
        color = controller->getColorofPixel(i);
        red = color.green();
        green = color.blue();
        blue = color.red();

        newcolor = QColor(red,green,blue);

        //nincs lekezelve, ha a fekete az átlátszó szín
        controller->setColorofPixel(i, newcolor);
    }
}

//ezt nemtom, van-e értelme megcsinálni
void ColorConverterTool::blackandwhite()
{
    int greyscale;
    QColor newcolor, color;

    for(int i = 0; i < numberofpixels; i++)
    {
        color = controller->getColorofPixel(i);
        greyscale = 0.2126 * color.redF() + 0.7152 * color.greenF() + 0.0722 * color.blueF();

        greyscale < 128 ? newcolor = QColor(0,0,0) : newcolor = QColor(255,255,255);

        //nincs lekezelve, ha a fekete az átlátszó szín
        controller->setColorofPixel(i, newcolor);
    }
}

void ColorConverterTool::greyscale()
{
    int greyscale;
    QColor newcolor, color;

    for(int i = 0; i < numberofpixels; i++)
    {
        color = controller->getColorofPixel(i);
        greyscale = 0.2126 * color.redF() + 0.7152 * color.greenF() + 0.0722 * color.blueF();

        newcolor = QColor(greyscale,greyscale,greyscale);

        //nincs lekezelve, ha a fekete az átlátszó szín
        controller->setColorofPixel(i, newcolor);
    }
}

void ColorConverterTool::colorfilter(QColor c)
{
    QColor color, newcolor;
    for(int i = 0; i < numberofpixels; i++)
    {
        color = controller->getColorofPixel(i);

        newcolor = QColor::fromHsl(c.hslHue(),color.hslSaturation(),color.lightness());

        //nincs lekezelve, ha a fekete az átlátszó szín
        controller->setColorofPixel(i, newcolor);
    }
}




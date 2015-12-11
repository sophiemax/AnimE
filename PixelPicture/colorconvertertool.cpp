#include "colorconvertertool.h"

ColorConverterTool::ColorConverterTool(Controller *c, int p)
{
    controller = c;
    numberofpixels = p;
}

ColorConverterTool::~ColorConverterTool()
{

}

void ColorConverterTool::convertColor(ColorConverterOptions::Options option)
{
    QColor c(255,0,0);
    switch(option)
    {
        case ColorConverterOptions::Options::inverz:
            inverz();
            break;
        case ColorConverterOptions::Options::blackandwhite:
            blackandwhite();
            break;
        case ColorConverterOptions::Options::greyscale:
            greyscale();
            break;
        case ColorConverterOptions::Options::filter:
            colorfilter(c);
            break;
        case ColorConverterOptions::Options::sepia:
            sepia();
            break;
        case ColorConverterOptions::Options::contrast:
            contrast();
            break;
        case ColorConverterOptions::Options::shiftright:
            shiftright();
            break;
        case ColorConverterOptions::Options::shiftleft:
            shiftleft();
            break;
    }
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
        controller->setColorofPixelConverted(i, newcolor);
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
        controller->setColorofPixelConverted(i, newcolor);
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
        controller->setColorofPixelConverted(i, newcolor);
    }
}

//ezt nemtom, van-e értelme megcsinálni
void ColorConverterTool::blackandwhite()
{
    float greyscale;
    QColor newcolor, color;

    for(int i = 0; i < numberofpixels; i++)
    {
        color = controller->getColorofPixel(i);
        greyscale = 0.2126 * color.redF() + 0.7152 * color.greenF() + 0.0722 * color.blueF();
        greyscale *= 255.0;

        greyscale < 128 ? newcolor = QColor(0,0,0) : newcolor = QColor(255,255,255);

        //nincs lekezelve, ha a fekete az átlátszó szín
        controller->setColorofPixelConverted(i, newcolor);
    }
}

void ColorConverterTool::greyscale()
{
    float greyscale;
    QColor newcolor, color;

    for(int i = 0; i < numberofpixels; i++)
    {
        color = controller->getColorofPixel(i);
        greyscale = 0.2126 * color.redF() + 0.7152 * color.greenF() + 0.0722 * color.blueF();

        newcolor = QColor(greyscale*255,greyscale*255,greyscale*255);

        //nincs lekezelve, ha a fekete az átlátszó szín
        controller->setColorofPixelConverted(i, newcolor);
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
        controller->setColorofPixelConverted(i, newcolor);
    }
}

void ColorConverterTool::sepia()
{
    float greyscale;
    QColor newcolor, color, tempcolor;

    for(int i = 0; i < numberofpixels; i++)
    {
        color = controller->getColorofPixel(i);
        greyscale = 0.2126 * color.redF() + 0.7152 * color.greenF() + 0.0722 * color.blueF();

        tempcolor = QColor(greyscale*255,greyscale*255*0.75,greyscale*255*0.25);
        newcolor = QColor::fromHsl(tempcolor.hslHue(), tempcolor.hslSaturation(), tempcolor.lightness()*1.25);
        //nincs lekezelve, ha a fekete az átlátszó szín
        controller->setColorofPixelConverted(i, newcolor);
    }
}

void ColorConverterTool::contrast()
{
    QColor color, newcolor;
    int sat, light;
    for(int i = 0; i < numberofpixels; i++)
    {
        color = controller->getColorofPixel(i);
        sat = 1.25 * color.saturation();
        light = 1.25 * color.value();

        if(sat >= 255)
            sat = 255;
        if(light >= 255)
            light = 255;
        newcolor = QColor::fromHsv(color.hslHue(), sat, light);

        //nincs lekezelve, ha a fekete az átlátszó szín
        controller->setColorofPixelConverted(i, newcolor);
    }
}




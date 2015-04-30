#include "ImageConverterTool.h"
#include <QPixmap>
#include "layerpixel.h"

ImageConverterTool::ImageConverterTool(PixelScene *pscene, int pixelsize, int pixelx, int pixely)
{
    scene = pscene;
    size = pixelsize;
    x = pixelx;
    y = pixely;
}

ImageConverterTool::~ImageConverterTool()
{

}

void ImageConverterTool::convertImage(QImage image)
{
    switch(importsettingsresolution)
    {
        case ImageConverterTool::ImportSettingsResolution::onlypixels:
            switch(importsettingscolor)
            {
                case ImageConverterTool::ImportSettingsColor::topleft:
                    onlypixelstopleftConvert(image);
                    break;
                case ImageConverterTool::ImportSettingsColor::center:
                    onlypixelscenterConvert(image);
                    break;
                case ImageConverterTool::ImportSettingsColor::corners:
                    onlypixelsaverageofcornersConvert(image);
                    break;
                case ImageConverterTool::ImportSettingsColor::average:
                    onlypixelsaverageConvert(image);
                    break;
            }
            break;
        case ImageConverterTool::ImportSettingsResolution::wholeimage:
            switch(importsettingscolor)
            {
                case ImageConverterTool::ImportSettingsColor::topleft:
                    topleftConvert(image);
                    break;
                case ImageConverterTool::ImportSettingsColor::center:
                    centerConvert(image);
                    break;
                case ImageConverterTool::ImportSettingsColor::corners:
                    averageofcornersConvert(image);
                    break;
                case ImageConverterTool::ImportSettingsColor::average:
                    averageConvert(image);
                    break;
            }
            break;
    }
}

void ImageConverterTool::topleftConvert(QImage image)
{
    foreach(Pixel *p, scene->pixels)
    {
        int index = p->index;

        scene->activeCanvas->activeLayer->pixels[index]->clear = false;
        scene->activeCanvas->activeLayer->pixels[index]->color = image.pixel(p->rect.left(),p->rect.top());

        scene->updateCombinedLayer(index);
        scene->updatePixel(index);
    }
}

void ImageConverterTool::onlypixelstopleftConvert(QImage image)
{
    for(int i = 0; i<x; i++)
    {
        int left = i*size;
        for(int j = 0; j<y; j++)
        {
            int index = j*x + i;
            int top = j*size;

            scene->activeCanvas->activeLayer->pixels[index]->clear = false;
            scene->activeCanvas->activeLayer->pixels[index]->color = image.pixel(left,top);

            scene->updateCombinedLayer(index);
            scene->updatePixel(index);

        }
    }
}

void ImageConverterTool::bottomrightConvert(QImage image)
{
    foreach(Pixel *p, scene->pixels)
    {
        int index = p->index;

        scene->activeCanvas->activeLayer->pixels[index]->clear = false;
        scene->activeCanvas->activeLayer->pixels[index]->color = image.pixel(p->rect.right(),p->rect.bottom());

        scene->updateCombinedLayer(index);
        scene->updatePixel(index);
    }
}

void ImageConverterTool::averageofcornersConvert(QImage image)
{
    foreach(Pixel *p, scene->pixels)
    {
        int index = p->index;

        QColor topleft = image.pixel(p->rect.left(),p->rect.top());
        QColor bottomleft = image.pixel(p->rect.left(),p->rect.bottom());
        QColor topright = image.pixel(p->rect.right(),p->rect.top());
        QColor bottomright = image.pixel(p->rect.right(),p->rect.bottom());

        QColor average((topleft.red()+bottomleft.red()+topright.red()+bottomright.red())/4,
                       (topleft.green()+bottomleft.green()+topright.green()+bottomright.green())/4,
                       (topleft.blue()+bottomleft.blue()+topright.blue()+bottomright.blue())/4);

        scene->activeCanvas->activeLayer->pixels[index]->clear = false;
        scene->activeCanvas->activeLayer->pixels[index]->color = average;

        scene->updateCombinedLayer(index);
        scene->updatePixel(index);
    }
}

void ImageConverterTool::onlypixelsaverageofcornersConvert(QImage image)
{
    for(int i = 0; i<x; i++)
    {
        int left = i*size;
        for(int j = 0; j<y; j++)
        {
            int index = j*x + i;
            int top = j*size;
            QRect rect(left, top, size, size);

            QColor topleft = image.pixel(rect.left(),rect.top());
            QColor bottomleft = image.pixel(rect.left(),rect.bottom());
            QColor topright = image.pixel(rect.right(),rect.top());
            QColor bottomright = image.pixel(rect.right(),rect.bottom());

            QColor average((topleft.red()+bottomleft.red()+topright.red()+bottomright.red())/4,
                           (topleft.green()+bottomleft.green()+topright.green()+bottomright.green())/4,
                           (topleft.blue()+bottomleft.blue()+topright.blue()+bottomright.blue())/4);

            scene->activeCanvas->activeLayer->pixels[index]->clear = false;
            scene->activeCanvas->activeLayer->pixels[index]->color = average;

            scene->updateCombinedLayer(index);
            scene->updatePixel(index);

        }
    }
}

void ImageConverterTool::centerConvert(QImage image)
{
    foreach(Pixel *p, scene->pixels)
    {
        int index = p->index;

        scene->activeCanvas->activeLayer->pixels[index]->clear = false;
        scene->activeCanvas->activeLayer->pixels[index]->color = image.pixel(p->rect.center().x(),p->rect.center().y());

        scene->updateCombinedLayer(index);
        scene->updatePixel(index);
    }
}

void ImageConverterTool::onlypixelscenterConvert(QImage image)
{
    for(int i = 0; i<x; i++)
    {
        int left = i*size;
        for(int j = 0; j<y; j++)
        {
            int index = j*x + i;
            int top = j*size;
            QRect rect(left, top, size, size);

            scene->activeCanvas->activeLayer->pixels[index]->clear = false;
            scene->activeCanvas->activeLayer->pixels[index]->color = image.pixel(rect.center().x(),rect.center().y());

            scene->updateCombinedLayer(index);
            scene->updatePixel(index);

        }
    }
}

void ImageConverterTool::averageConvert(QImage image)
{
    int size = scene->pixelSize;

    foreach(Pixel *p, scene->pixels)
    {
        int index = p->index;

        int top = p->rect.top();
        int left = p->rect.left();
        int red = 0, green = 0, blue = 0;

        for(int i = 0; i<=size; i++)
        {
            for(int j = 0; j<=size; j++)
            {
                QColor color = image.pixel(left+i,top+j);
                red += color.red();
                green += color.green();
                blue += color.blue();
            }
        }

        red /= pow((size+1),2);
        blue /= pow((size+1),2);
        green /= pow((size+1),2);

        QColor average(red,green,blue);

        scene->activeCanvas->activeLayer->pixels[index]->clear = false;
        scene->activeCanvas->activeLayer->pixels[index]->color = average;

        scene->updateCombinedLayer(index);
        scene->updatePixel(index);
    }
}

void ImageConverterTool::onlypixelsaverageConvert(QImage image)
{
    for(int i = 0; i<x; i++)
    {
        int left = i*size;
        for(int j = 0; j<y; j++)
        {
            int index = j*x + i;
            int top = j*size;
            int red = 0, green = 0, blue = 0;

            for(int k = 0; k<=size; k++)
            {
                for(int l = 0; l<=size; l++)
                {
                    QColor color = image.pixel(left+k,top+l);
                    red += color.red();
                    green += color.green();
                    blue += color.blue();
                }
            }

            red /= pow((size+1),2);
            blue /= pow((size+1),2);
            green /= pow((size+1),2);

            QColor average(red,green,blue);

            scene->activeCanvas->activeLayer->pixels[index]->clear = false;
            scene->activeCanvas->activeLayer->pixels[index]->color = average;

            scene->updateCombinedLayer(index);
            scene->updatePixel(index);
        }
    }
}

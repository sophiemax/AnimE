#include "ImageConverterTool.h"
#include <QPixmap>
#include "layerpixel.h"

ImageConverterTool::ImageConverterTool(Controller *c, int pixelsize, int pixelx, int pixely)
{
    controller = c;
    size = pixelsize;
    x = pixelx;
    y = pixely;
}

ImageConverterTool::~ImageConverterTool()
{

}

void ImageConverterTool::convertImage(QImage image)
{
    QImage scaled;
    switch(importsettingsresolution)
    {
        case ImageConverterTool::ImportSettingsResolution::onlypixels:
            scaled = image.scaled(controller->getOnlyPixelsWidth() + 1, controller->getOnlyPixelsHeight() + 1);
            switch(importsettingscolor)
            {
                case ImageConverterTool::ImportSettingsColor::topleft:
                    onlypixelstopleftConvert(scaled);
                    break;
                case ImageConverterTool::ImportSettingsColor::center:
                    onlypixelscenterConvert(scaled);
                    break;
                case ImageConverterTool::ImportSettingsColor::corners:
                    onlypixelsaverageofcornersConvert(scaled);
                    break;
                case ImageConverterTool::ImportSettingsColor::average:
                    onlypixelsaverageConvert(scaled);
                    break;
            }
            break;
        case ImageConverterTool::ImportSettingsResolution::wholeimage:
            scaled = image.scaled(controller->getWidth() + 1, controller->getHeight() + 1);
            switch(importsettingscolor)
            {
                case ImageConverterTool::ImportSettingsColor::topleft:
                    topleftConvert(scaled);
                    break;
                case ImageConverterTool::ImportSettingsColor::center:
                    centerConvert(scaled);
                    break;
                case ImageConverterTool::ImportSettingsColor::corners:
                    averageofcornersConvert(scaled);
                    break;
                case ImageConverterTool::ImportSettingsColor::average:
                    averageConvert(scaled);
                    break;
            }
            break;
    }
}

void ImageConverterTool::topleftConvert(QImage image)
{
    for(int index = 0; index < controller->numberofPixels(); index++)
    {
        QRect rect = controller->getPixelRect(index);
        QColor color = image.pixel(rect.left(),rect.top());

        setColorofPixel(index, color);
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

            QColor color = image.pixel(left,top);

            setColorofPixel(index, color);
        }
    }
}

/*void ImageConverterTool::bottomrightConvert(QImage image)
{
    foreach(Pixel *p, scene->pixels)
    {
        int index = p->index;

        scene->activeCanvas->activeLayer->pixels[index]->clear = false;
        scene->activeCanvas->activeLayer->pixels[index]->color = image.pixel(p->rect.right(),p->rect.bottom());

        scene->updateCombinedLayer(index);
        scene->updatePixel(index);
    }
}*/

void ImageConverterTool::averageofcornersConvert(QImage image)
{
    for(int index = 0; index < controller->numberofPixels(); index++)
    {
        QRect rect = controller->getPixelRect(index);

        QColor topleft = image.pixel(rect.left(),rect.top());
        QColor bottomleft = image.pixel(rect.left(),rect.bottom());
        QColor topright = image.pixel(rect.right(),rect.top());
        QColor bottomright = image.pixel(rect.right(),rect.bottom());

        QColor average((topleft.red()+bottomleft.red()+topright.red()+bottomright.red())/4,
                       (topleft.green()+bottomleft.green()+topright.green()+bottomright.green())/4,
                       (topleft.blue()+bottomleft.blue()+topright.blue()+bottomright.blue())/4);

        setColorofPixel(index, average);
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

            setColorofPixel(index, average);
        }
    }
}

void ImageConverterTool::centerConvert(QImage image)
{
    for(int index = 0; index < controller->numberofPixels(); index++)
    {
        QRect rect = controller->getPixelRect(index);

        QColor color = image.pixel(rect.center().x(),rect.center().y());

        setColorofPixel(index, color);
    }
}

void ImageConverterTool::onlypixelscenterConvert(QImage image)
{
    QTextStream(stdout) << image.size().width() << ";" << image.size().height() << endl;
    for(int i = 0; i<x; i++)
    {
        int left = i*size;
        for(int j = 0; j<y; j++)
        {
            int index = j*x + i;
            int top = j*size;
            QRect rect(left, top, size, size);

            QColor color = image.pixel(rect.center().x(),rect.center().y());

            setColorofPixel(index, color);

            //QTextStream(stdout) << "left: " << left << " top: " << top << endl;
        }
    }
}

void ImageConverterTool::averageConvert(QImage image)
{
    for(int index = 0; index < controller->numberofPixels(); index++)
    {
        QRect rect = controller->getPixelRect(index);

        int top = rect.top();
        int left = rect.left();
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

        setColorofPixel(index, average);
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

            setColorofPixel(index, average);
        }
    }
}

void ImageConverterTool::setColorofPixel(int index, QColor color)
{
    if(blackisclear && color == Qt::black)
    {
        controller->clearPixel(index);
    }
    else
    {
        controller->setColorofPixel(index, color);
    }
}

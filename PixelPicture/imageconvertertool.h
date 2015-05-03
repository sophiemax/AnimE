#ifndef IMAGECONVERTERTOOL_H
#define IMAGECONVERTERTOOL_H

#include <QImage>
#include "controller.h"

class Controller;

class ImageConverterTool
{
    Q_ENUMS(ImportSetting)
public:

    enum class ImportSettingsResolution
      {
         onlypixels,
         wholeimage
      };

    enum class ImportSettingsColor
    {
        topleft,
        center,
        corners,
        average
    };

    ImageConverterTool(Controller *c, int pixelsize, int pixelx, int pixely);
    ~ImageConverterTool();

    void convertImage(QImage image);
    void topleftConvert(QImage image);
    void onlypixelstopleftConvert(QImage image);
    void bottomrightConvert(QImage image);
    void averageofcornersConvert(QImage image);
    void onlypixelsaverageofcornersConvert(QImage image);
    void centerConvert(QImage image);
    void onlypixelscenterConvert(QImage image);
    void averageConvert(QImage image);
    void onlypixelsaverageConvert(QImage image);

    void setColorofPixel(int index, QColor color);

    ImportSettingsResolution importsettingsresolution = ImageConverterTool::ImportSettingsResolution::onlypixels;
    ImportSettingsColor importsettingscolor = ImageConverterTool::ImportSettingsColor::center;

    bool blackisclear = false;

private:
    Controller *controller;
    int size, x, y;
};

#endif // IMAGECONVERTERTOOL_H

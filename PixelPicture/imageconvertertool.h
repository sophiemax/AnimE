#ifndef IMAGECONVERTERTOOL_H
#define IMAGECONVERTERTOOL_H

#include <QImage>
#include "pixelscene.h"

class PixelScene;

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

    ImageConverterTool(PixelScene *scene, int pixelsize, int pixelx, int pixely);
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

    ImportSettingsResolution importsettingsresolution = ImageConverterTool::ImportSettingsResolution::onlypixels;
    ImportSettingsColor importsettingscolor = ImageConverterTool::ImportSettingsColor::center;

    //bool onlypixels = true, wholeimage = false, topleft = false, center = true, corners = false, average = false;
private:
    PixelScene *scene;
    int size, x, y;
};

#endif // IMAGECONVERTERTOOL_H

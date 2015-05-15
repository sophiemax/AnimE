#ifndef IMAGECONVERTERTOOL_H
#define IMAGECONVERTERTOOL_H

#include <QImage>
#include "controller.h"

class Controller;

//a kép betöltésekor alkalmazandó algoritmus paramétereit, beállításait kezeli
class ImageConverterTool
{
    Q_ENUMS(ImportSetting)
public:

    //méretre vonatkozó beállítások
    enum class ImportSettingsResolution
      {
        //csak az ablakokat veszi vászonnak, nem veszi figyelembe a köztük lévő részt
         onlypixels,
        //figyelembe veszi konvertáláskor az ablakok között lévő részt is
         wholeimage
      };

    //egy pixel színére vonatkozó beállítások
    enum class ImportSettingsColor
    {
        //a bal felső sarkot veszi alapszínnek
        topleft,
        //a képrészlet közepét veszi alapszínnek
        center,
        //A képrészlet sarkai alapján átlagol
        corners,
        //a képrészlet összes pixelét átlagolja
        average
    };

    //convertertool létrehozása, a képkonvertáláshoz szükséges paraméterekkel: a pixel mérete, a kijelző oszlopainak és sorainak száma
    ImageConverterTool(Controller *c, int pixelsize, int pixelx, int pixely);
    ~ImageConverterTool();

    //kép konvertálása
    void convertImage(QImage image);
    //bal felső sarok alapján konvertál
    void topleftConvert(QImage image);
    //bal felső sarok alapján konvertál, az ablakok közti rész figyelmen kívül hagyásával
    void onlypixelstopleftConvert(QImage image);
    //jobb alsó sarok alapján konvertál
    void bottomrightConvert(QImage image);
    //sarkok átlaga alapján konvertál
    void averageofcornersConvert(QImage image);
    //sarkok átlaga alapján konvertál, az ablakok közti rész figyelmen kívül hagyásával
    void onlypixelsaverageofcornersConvert(QImage image);
    //a közép alapján konvertál
    void centerConvert(QImage image);
    //közép alapján konvertál , az ablakok közti rész figyelmen kívül hagyásával
    void onlypixelscenterConvert(QImage image);
    //minden pixel átlaga alapján konvertál
    void averageConvert(QImage image);
    //minden pixel átlaga alapján konvertál, az ablakok közti rész figyelmen kívül hagyásával
    void onlypixelsaverageConvert(QImage image);

    //pixel színének beállítása
    void setColorofPixel(int index, QColor color);

    //felbontás beállításai
    ImportSettingsResolution importsettingsresolution = ImageConverterTool::ImportSettingsResolution::onlypixels;
    ImportSettingsColor importsettingscolor = ImageConverterTool::ImportSettingsColor::center;

    bool blackisclear = false;

private:
    //pixelméret, kijelző szélessége és magassága
    int size, x, y;
    //módosítások kommunikálásához
    Controller *controller;
};

#endif // IMAGECONVERTERTOOL_H

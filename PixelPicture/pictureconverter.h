#ifndef PICTURECONVERTER_H
#define PICTURECONVERTER_H

#include <QImage>
#include "pixelscene.h"

class pictureConverter
{
public:
    pictureConverter(PixelScene *scene);
    ~pictureConverter();

    void centerColor(PixelScene *scene);
private:
    QImage *image;
};

#endif // PICTURECONVERTER_H

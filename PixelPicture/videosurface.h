#ifndef VIDEOSURFACE_H
#define VIDEOSURFACE_H

#include <QAbstractVideoSurface>
#include "controller.h"

class VideoSurface : public QAbstractVideoSurface
{
public:
    //a videosurface létrehozása megfelelő controller és player pointerrel
    VideoSurface(Controller *c, QMediaPlayer *p);
    ~VideoSurface();

    //megvalósítás szempontjából nem lényeges, de az interface implementálásához szükséges
    QList<QVideoFrame::PixelFormat> supportedPixelFormats(
            QAbstractVideoBuffer::HandleType handleType = QAbstractVideoBuffer::NoHandle) const;

    //az aktuális frame-et kezeli
    bool present(const QVideoFrame &frame);

    //új videó esetén a szükséges változókat nullába állítja
    void reset();
    void settings(bool tr, int f, int t);

private:
    //módosítások lekommunikálásához
    Controller *controller;
    //a lejátszást végrehajtó player
    QMediaPlayer *player;

    //a videó eddigi hossza
    float videosum = 0.0;
    bool trim;
    int from, to;
};

#endif // VIDEOSURFACE_H

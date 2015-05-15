#ifndef VIDEOSURFACE_H
#define VIDEOSURFACE_H

#include <QAbstractVideoSurface>
#include "controller.h"

class VideoSurface : public QAbstractVideoSurface
{
public:
    VideoSurface(Controller *c, QMediaPlayer *p);
    ~VideoSurface();

    QList<QVideoFrame::PixelFormat> supportedPixelFormats(
            QAbstractVideoBuffer::HandleType handleType = QAbstractVideoBuffer::NoHandle) const;

    bool present(const QVideoFrame &frame);

    void reset();

private:
    //módosítások lekommunikálásához
    Controller *controller;
    //a lejátszást végrehajtó player
    QMediaPlayer *player;

    //a videó eddigi hossza
    float videosum = 0.0;
};

#endif // VIDEOSURFACE_H

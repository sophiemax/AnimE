#ifndef VIDEOSURFACE_H
#define VIDEOSURFACE_H

#include <QAbstractVideoSurface>
#include "pixelscene.h"

class VideoSurface : public QAbstractVideoSurface
{
public:
    VideoSurface(PixelScene *s, QMediaPlayer *p);
    ~VideoSurface();

    QList<QVideoFrame::PixelFormat> supportedPixelFormats(
            QAbstractVideoBuffer::HandleType handleType = QAbstractVideoBuffer::NoHandle) const;

    bool present(const QVideoFrame &frame);

private:
    PixelScene *scene;
    QMediaPlayer *player;

    float videosum = 0.0;
};

#endif // VIDEOSURFACE_H

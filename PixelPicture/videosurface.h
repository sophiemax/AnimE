#ifndef VIDEOSURFACE_H
#define VIDEOSURFACE_H

#include <QAbstractVideoSurface>
#include "pixelscene.h"

class VideoSurface : public QAbstractVideoSurface
{
public:
    VideoSurface(PixelScene *s);
    ~VideoSurface();

    QList<QVideoFrame::PixelFormat> supportedPixelFormats(
            QAbstractVideoBuffer::HandleType handleType = QAbstractVideoBuffer::NoHandle) const;

    bool present(const QVideoFrame &frame);

private:
    PixelScene *scene;
};

#endif // VIDEOSURFACE_H

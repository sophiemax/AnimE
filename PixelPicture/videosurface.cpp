#include "videosurface.h"

VideoSurface::VideoSurface(Controller *c, QMediaPlayer *p)
{
    controller = c;
    player = p;
}

VideoSurface::~VideoSurface()
{

}

QList<QVideoFrame::PixelFormat> VideoSurface::supportedPixelFormats(QAbstractVideoBuffer::HandleType handleType) const
{
    Q_UNUSED(handleType);

    return QList<QVideoFrame::PixelFormat>() << QVideoFrame::Format_RGB32;
}

bool VideoSurface::present(const QVideoFrame &frame)
{
    QVideoFrame currentframe = frame;
    if(currentframe.map(QAbstractVideoBuffer::ReadOnly))
    {
        QImage::Format imageFormat = QVideoFrame::imageFormatFromPixelFormat(currentframe.pixelFormat());

        QImage image(currentframe.bits(),
                     currentframe.width(),
                     currentframe.height(),
                     currentframe.bytesPerLine(),
                     imageFormat);

        int timespan = player->position() - videosum;
        controller->addFrame(timespan);
        videosum += timespan;

        controller->importImage(image);

        return true;
    }
    return false;
}

void VideoSurface::reset()
{
    videosum = 0.0;
}

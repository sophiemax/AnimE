#include "videosurface.h"

#include "frame.h"
#include "canvas.h"

VideoSurface::VideoSurface(PixelScene *s, QMediaPlayer *p)
{
    scene = s;
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

        Canvas *c = new Canvas(scene->pixels.size());
        Frame* f = new Frame(c);

        f->timespan = player->position() - videosum;
        videosum += f->timespan;
        scene->timesum += f->timespan;

        scene->activeCanvas = c;
        scene->importImage(image);

        scene->frames.append(f);

        return true;
    }
    return false;
}

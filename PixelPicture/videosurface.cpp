#include "videosurface.h"

#include "frame.h"
#include "canvas.h"

VideoSurface::VideoSurface(PixelScene *s)
{
    scene = s;
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
    QMediaPlayer *player = new QMediaPlayer(sender());
    QTextStream(stdout) << player->position() << endl;
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

        f->timespan = scene->interval;
        scene->timesum += f->timespan;

        scene->activeCanvas = c;
        scene->importImage(image);

        scene->frames.append(f);

        return true;
    }
    return false;
}

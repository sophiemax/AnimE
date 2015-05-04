#include "exporttool.h"
#include <QXmlStreamWriter>
#include <QFile>
#include <QTextStream>

ExportTool::ExportTool(Controller* c)
{
    controller = c;
}

ExportTool::~ExportTool()
{

}

void ExportTool::exportFile(QString fileName)
{
    QString document;
    QXmlStreamWriter stream(&document);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();

    int pixelsinaColumn = controller->pixelsinaColumn();
    int pixelsinaRow = controller->pixelsinaRow();

    for(int animation = 0; animation < controller->numberofAnimations(); animation++)
    {
        stream.writeStartElement("animation");

        stream.writeTextElement("timesum", QString::number(controller->getTimesum(animation)));
        stream.writeTextElement("pixelsinacolumn", QString::number(pixelsinaColumn));
        stream.writeTextElement("pixelsinarow", QString::number(pixelsinaRow));
        stream.writeTextElement("name", controller->getAnimationName(animation));

        for(int frame = 0; frame < controller->numberofFrames(animation); frame++)
        {
            stream.writeStartElement("frame");
            stream.writeTextElement("timespan", QString::number(controller->getTimespan(animation,frame)));
            stream.writeTextElement("name", controller->getFrameName(animation,frame));

            stream.writeStartElement("canvas");
            stream.writeTextElement("pixelsinacolumn", QString::number(pixelsinaColumn));
            stream.writeTextElement("pixelsinarow", QString::number(pixelsinaRow));

            for(int layer = 0; layer < controller->numberofLayers(animation, frame); layer++)
            {
                int numberofrows = controller->getnumberofrows(animation, frame, layer);
                int numberofcolumns = controller->getnumberofcolumns(animation, frame, layer);
                stream.writeStartElement("layer");
                stream.writeTextElement("originalnumberofrows", QString::number(pixelsinaColumn));
                stream.writeTextElement("originalnumberofcolumns", QString::number(pixelsinaRow));
                stream.writeTextElement("numberofcolums", QString::number(numberofcolumns));
                stream.writeTextElement("numberofrows", QString::number(numberofrows));
                stream.writeTextElement("transparent", QString::number(controller->getTransparency(animation,frame,layer)));
                stream.writeTextElement("name", controller->getLayerName(animation, frame, layer));

                for(int pixel = 0; pixel < numberofcolumns*numberofrows; pixel++)
                {
                    stream.writeStartElement("layerpixel");
                    stream.writeTextElement("index", QString::number(pixel));
                    stream.writeTextElement("clear", QString::number(controller->isPixelClear(animation,frame,layer,pixel)));
                    stream.writeTextElement("color", controller->getColorofPixel(animation,frame,layer,pixel).name());
                    stream.writeEndElement(); // layerpixel
                }
                stream.writeEndElement(); // layer
            }

            stream.writeEndElement(); // canvas

            stream.writeEndElement(); // frame

        }
        stream.writeEndElement(); // animation
    }

    stream.writeEndDocument();

    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            // error message
        } else {
            QTextStream stream(&file);
            stream << document;
            stream.flush();
            file.close();
        }
    }
}


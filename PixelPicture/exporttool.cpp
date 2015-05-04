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
    bool clear;
    QColor color;
    int counter;

    int pixelsinaColumn = controller->pixelsinaColumn();
    int pixelsinaRow = controller->pixelsinaRow();

    stream.writeStartElement("anime");

    stream.writeTextElement("pixelsinacolumn", QString::number(pixelsinaColumn));
    stream.writeTextElement("pixelsinarow", QString::number(pixelsinaRow));

    for(int animation = 0; animation < controller->numberofAnimations(); animation++)
    {
        stream.writeStartElement("animation");

        stream.writeTextElement("timesum", QString::number(controller->getTimesum(animation)));
        stream.writeTextElement("animationname", controller->getAnimationName(animation));

        for(int frame = 0; frame < controller->numberofFrames(animation); frame++)
        {
            stream.writeStartElement("frame");
            stream.writeTextElement("timespan", QString::number(controller->getTimespan(animation,frame)));
            stream.writeTextElement("framename", controller->getFrameName(animation,frame));

            stream.writeStartElement("canvas");

            for(int layer = 0; layer < controller->numberofLayers(animation, frame); layer++)
            {
                int numberofrows = controller->getnumberofrows(animation, frame, layer);
                int numberofcolumns = controller->getnumberofcolumns(animation, frame, layer);
                stream.writeStartElement("layer");
                stream.writeTextElement("originalnumberofrows", QString::number(pixelsinaColumn));
                stream.writeTextElement("originalnumberofcolumns", QString::number(pixelsinaRow));
                stream.writeTextElement("transparent", QString::number(controller->getTransparency(animation,frame,layer)));
                stream.writeTextElement("layername", controller->getLayerName(animation, frame, layer));

                clear = controller->isPixelClear(animation,frame,layer,0);
                color = controller->getColorofPixel(animation,frame,layer,0);
                counter = 1;
                for(int pixel = 0; pixel < numberofcolumns*numberofrows; pixel++)
                {
                    if(controller->isPixelClear(animation,frame,layer,pixel) == clear && controller->getColorofPixel(animation,frame,layer,pixel) == color)
                        counter++;
                    else
                    {
                        QString data = QString::number(counter);
                        data.append(",");
                        data.append(QString::number(clear));
                        data.append(",");
                        data.append(color.name());
                        stream.writeTextElement("data", data);

                        clear = controller->isPixelClear(animation,frame,layer,pixel);
                        color = controller->getColorofPixel(animation,frame,layer,pixel);
                        counter = 1;
                    }
                }
                stream.writeEndElement(); // layer
            }

            stream.writeEndElement(); // canvas

            stream.writeEndElement(); // frame

        }
        stream.writeEndElement(); // animation
    }

    stream.writeEndElement(); // anime
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


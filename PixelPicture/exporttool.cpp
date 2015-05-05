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

    QStringList names = controller->getNameList();

    stream.writeTextElement(names[0], QString::number(pixelsinaColumn)); //pixelsinacolumn
    stream.writeTextElement(names[1], QString::number(pixelsinaRow)); //pixelsinarow

    for(int animation = 0; animation < controller->numberofAnimations(); animation++)
    {
        stream.writeStartElement(names[2]); //animation

        stream.writeTextElement(names[3], QString::number(controller->getTimesum(animation))); //timesum
        stream.writeTextElement(names[4], controller->getAnimationName(animation)); //animationname

        for(int frame = 0; frame < controller->numberofFrames(animation); frame++)
        {
            stream.writeStartElement(names[5]); //frame
            stream.writeTextElement(names[6], QString::number(controller->getTimespan(animation,frame))); //timespan
            stream.writeTextElement(names[7], controller->getFrameName(animation,frame)); //framename

            stream.writeStartElement(names[8]); //canvas

            for(int layer = 0; layer < controller->numberofLayers(animation, frame); layer++)
            {
                int numberofrows = controller->getnumberofrows(animation, frame, layer);
                int numberofcolumns = controller->getnumberofcolumns(animation, frame, layer);
                stream.writeStartElement(names[9]); //layer
                stream.writeTextElement(names[10], QString::number(numberofrows)); //numberofrows
                stream.writeTextElement(names[11], QString::number(numberofcolumns)); //numberofcolumns
                stream.writeTextElement(names[12], QString::number(controller->getTransparency(animation,frame,layer))); //transparent
                stream.writeTextElement(names[13], controller->getLayerName(animation, frame, layer)); //layername

                clear = controller->isPixelClear(animation,frame,layer,0);
                color = controller->getColorofPixel(animation,frame,layer,0);
                counter = 1;
                for(int pixel = 1; pixel < numberofcolumns*numberofrows; pixel++)
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
                        stream.writeTextElement(names[14], data); //data of layerpixel

                        clear = controller->isPixelClear(animation,frame,layer,pixel);
                        color = controller->getColorofPixel(animation,frame,layer,pixel);
                        counter = 1;
                    }
                }
                //Az utolsó adag layerpixelt is exportáljuk
                QString data = QString::number(counter);
                data.append(",");
                data.append(QString::number(clear));
                data.append(",");
                data.append(color.name());
                stream.writeTextElement(names[14], data); //data of layerpixel
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


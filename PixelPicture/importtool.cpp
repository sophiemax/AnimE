#include "importtool.h"
#include <QXmlStreamReader>

ImportTool::ImportTool(Controller *c)
{
    controller = c;
}

ImportTool::~ImportTool()
{

}

void ImportTool::importFile(QString fileName)
{
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);

    QXmlStreamReader xml(&file);

    int animation = 0;
    int frame = 0;
    int layer = 0;

    controller->clearAll();

    QStringList names = controller->getNameList();

    while (!xml.atEnd())
    {
        xml.readNext();
        if(xml.isStartElement())
        {
            // Read the tag name.

            QTextStream(stdout) << "startElement:" << endl;
            QString name(xml.name().toString());
            //QString element(xml.readElementText());
            QTextStream(stdout) << name << endl;
            //QTextStream(stdout) << "innerElement:" << endl;
            //QTextStream(stdout) << element << endl;
            //QTextStream(stdout) << "done:" << endl;
            QString element;
            switch(names.indexOf(name))
            {
                case 0: //pixelsinacolumn
                    element = xml.readElementText();
                    controller->setpixelsinacolumn(element.toInt());
                    break;
                case 1: //pixelsinarow
                    element = xml.readElementText();
                    controller->setpixelsinarow(element.toInt());
                    break;
                case 2: //animation
                    controller->addAnimation(animation);
                    break;
                case 3: //timesum
                    element = xml.readElementText();
                    controller->setTimesum(animation,element.toFloat());
                    break;
                case 4: //animationname
                    element = xml.readElementText();
                    controller->setAnimationName(animation,element);
                    break;
                case 5: //frame
                    controller->addFrameIndexed(animation, frame);
                    break;
                case 6: //timespan
                    element = xml.readElementText();
                    controller->setTimespan(animation, frame, element.toFloat());
                    break;
                case 7: //framename
                    element = xml.readElementText();
                    controller->setFrameName(animation, frame, element);
                    break;
                case 8: //canvas
                    controller->addCanvas(animation, frame);
                    break;
                case 9: //layer
                    controller->addLayer(animation, frame, layer);
                    break;
                case 10: //numberofrows
                    element = xml.readElementText();
                    controller->setNumberofrows(animation, frame, layer, element.toInt());
                    break;
                case 11: //numberofcolumns
                    element = xml.readElementText();
                    controller->setNumberofcolumns(animation, frame, layer, element.toInt());
                    break;
                case 12: //transparent
                    element = xml.readElementText();
                    controller->setLayerTransparency(animation, frame, layer, element.toInt());
                    break;
                case 13: //layername
                    element = xml.readElementText();
                    controller->setLayerName(animation, frame, layer, element);
                    break;
                case 14: //data
                    element = xml.readElementText();
                    controller->addLayerPixels(animation, frame, layer, element);
                    break;
                default:
                    break;
            }
        }
        else if(xml.isEndElement())
        {

            QTextStream(stdout) << "endElement:" << endl;
            QString name(xml.name().toString());
            QTextStream(stdout) << name << endl;

            switch(names.indexOf(name))
            {
                case 2: //animation
                    animation++;
                    break;
                case 5: //frame
                    frame++;
                    break;
                case 9: //layer
                    layer++;
                    break;
                default:
                    break;
            }
        } else {
            QTextStream(stdout) << "egyik se" << endl;
        }
    }
    if (xml.hasError()) {
        //QMessageBox::critical(this, tr("Error"), tr("Could not parse XML"));
    }
}

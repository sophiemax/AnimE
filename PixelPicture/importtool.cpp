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
            QString name(xml.name().toString());
            QString element;
            switch(names.indexOf(name))
            {
                case 0: //pixelsinacolumn
                    QTextStream(stdout) << name << endl;
                    element = xml.readElementText();
                    controller->setpixelsinacolumn(element.toInt());
                    break;
                case 1: //pixelsinarow
                    QTextStream(stdout) << name << endl;
                    element = xml.readElementText();
                    controller->setpixelsinarow(element.toInt());
                    break;
                case 2: //animation
                    QTextStream(stdout) << name << endl;
                    controller->addAnimation(animation);
                    break;
                case 3: //timesum
                    QTextStream(stdout) << name << endl;
                    element = xml.readElementText();
                    controller->setTimesum(animation,element.toFloat());
                    break;
                case 4: //animationname
                    QTextStream(stdout) << name << endl;
                    element = xml.readElementText();
                    controller->setAnimationName(animation,element);
                    break;
                case 5: //frame
                    QTextStream(stdout) << name << endl;
                    controller->addFrameIndexed(animation, frame);
                    break;
                case 6: //timespan
                    QTextStream(stdout) << name << endl;
                    element = xml.readElementText();
                    controller->setTimespan(animation, frame, element.toFloat());
                    break;
                case 7: //framename
                    QTextStream(stdout) << name << endl;
                    element = xml.readElementText();
                    controller->setFrameName(animation, frame, element);
                    break;
                case 8: //canvas
                    QTextStream(stdout) << name << endl;
                    controller->addCanvas(animation, frame);
                    break;
                case 9: //layer
                    QTextStream(stdout) << name << endl;
                    controller->addLayer(animation, frame, layer);
                    break;
                case 10: //numberofrows
                    QTextStream(stdout) << name << endl;
                    element = xml.readElementText();
                    controller->setNumberofrows(animation, frame, layer, element.toInt());
                    break;
                case 11: //numberofcolumns
                    QTextStream(stdout) << name << endl;
                    element = xml.readElementText();
                    controller->setNumberofcolumns(animation, frame, layer, element.toInt());
                    break;
                case 12: //transparent
                    QTextStream(stdout) << name << endl;
                    element = xml.readElementText();
                    controller->setLayerTransparency(animation, frame, layer, element.toInt());
                    break;
                case 13: //layername
                    QTextStream(stdout) << name << endl;
                    element = xml.readElementText();
                    controller->setLayerName(animation, frame, layer, element);
                    break;
                case 14: //data
                    QTextStream(stdout) << name << endl;
                    element = xml.readElementText();
                    controller->addLayerPixels(animation, frame, layer, element);
                    break;
                default:
                    break;
            }
        }
        else if(xml.isEndElement())
        {
            QString name(xml.name().toString());

            switch(names.indexOf(name))
            {
                case 2: //animation
                    animation++;
                    frame = 0;
                    layer = 0;
                    break;
                case 5: //frame
                    frame++;
                    layer = 0;
                    break;
                case 9: //layer
                    layer++;
                    break;
                default:
                    break;
            }
        }
    }
    if (xml.hasError()) {
        //QMessageBox::critical(this, tr("Error"), tr("Could not parse XML"));
    }
}

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
    int pixel = 0;

    controller->clearAll();

    while (!xml.atEnd())
    {
        xml.readNext();
        if(xml.isStartElement())
        {
            // Read the tag name.
            QString name(xml.name().toString());
            if(name == "animation")
            {
                controller->addAnimation(0);
            }
            // Check in settings map, whether there's already an entry. If not, insert.
            /*if(!_settingsMap.contains(sec))
                _settingsMap.insert(sec, xml.attributes());*/
        }
    }
    if (xml.hasError()) {
        //QMessageBox::critical(this, tr("Error"), tr("Could not parse XML"));
    }
}

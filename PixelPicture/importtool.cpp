#include "importtool.h"

ImportTool::ImportTool(Controller *c)
{
    controller = c;
}

ImportTool::~ImportTool()
{

}

void ImportTool::importFile(QString fileName)
{
    /*QFile file;
    if (!fileName.isEmpty())
    {
        file = QFile::QFile(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
            return;
        }
    }

    QXmlStreamReader xml(&file);

    int animation = 0;
    int frame = 0;
    int layer = 0;
    int pixel = 0;

    while (!xml.atEnd())
    {
        xml.readNext();
        if(xmlStream.isStartElement())
        {
            // Read the tag name.
            QString name(xmlStream.name().toString());
            if(name == "animation")
                controller->addAnimation();
            if(name)
            // Check in settings map, whether there's already an entry. If not, insert.
            if(!_settingsMap.contains(sec))
                _settingsMap.insert(sec, xmlStream.attributes());
        }
    }
    if (xml.hasError()) {
        QMessageBox::critical(this, tr("Error"), tr("Could not parse XML"));
    }
    file.close();*/
}

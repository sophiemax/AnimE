#ifndef EXPORTTOOL_H
#define EXPORTTOOL_H

#include <QString>
#include "controller.h"

class Controller;

class ExportTool
{
public:
    ExportTool(Controller *c);
    ~ExportTool();

    void exportFile(QString fileName);
private:
    //módosítások kommunikálásához
    Controller *controller;
};

#endif // EXPORTTOOL_H

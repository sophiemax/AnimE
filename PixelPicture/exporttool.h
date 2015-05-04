#ifndef EXPORTTOOL_H
#define EXPORTTOOL_H

#include <QString>
#include "controller.h"

class ExportTool
{
public:
    ExportTool(Controller *c);
    ~ExportTool();

    void exportFile(QString fileName);
private:
    Controller *controller;
};

#endif // EXPORTTOOL_H

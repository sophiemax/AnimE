#ifndef IMPORTTOOL_H
#define IMPORTTOOL_H

#include "controller.h"

class ImportTool
{
public:
    ImportTool(Controller *c);
    ~ImportTool();

    void importFile(QString fileName);
private:
    Controller *controller;
};

#endif // IMPORTTOOL_H

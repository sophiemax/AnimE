#ifndef IMPORTTOOL_H
#define IMPORTTOOL_H

#include "controller.h"

class Controller;

class ImportTool
{
public:
    ImportTool(Controller *c);
    ~ImportTool();

    void importFile(QString fileName);
private:
    //módosítások lekommunikálásához
    Controller *controller;
};

#endif // IMPORTTOOL_H

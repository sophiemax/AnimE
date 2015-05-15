#include "painttool.h"

PaintTool::PaintTool(QObject *parent):
QObject(parent)
{
}

PaintTool::~PaintTool()
{

}

void PaintTool::setController(Controller *c)
{
    controller = c;
}


#include "tool.h"

Tool::Tool(QObject *parent):
QObject(parent)
{
}

Tool::~Tool()
{

}

void Tool::setController(Controller *c)
{
    controller = c;
}


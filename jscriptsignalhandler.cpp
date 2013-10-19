#include "jscriptsignalhandler.h"

JScriptSignalHandler::JScriptSignalHandler(QObject *parent) :
    QObject(parent)
{
}

void JScriptSignalHandler::setParentWidget(QWidget *parentWidget)
{
    this->parentWidget = parentWidget;
}

void JScriptSignalHandler::showWindow()
{
    qDebug("[debug] JavaScript signaled showWindow!");
    if (this->parentWidget != NULL)
    {
        this->parentWidget->show();
    }
}

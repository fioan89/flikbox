#ifndef JSCRIPTSIGNALHANDLER_H
#define JSCRIPTSIGNALHANDLER_H

#include <QObject>
#include <QWidget>
class JScriptSignalHandler : public QObject
{
    Q_OBJECT

private:
    QWidget* parentWidget;
public:
    explicit JScriptSignalHandler(QObject *parent = 0);

    /**
     * @brief setParentWidget Sets the parent widget that should hanlde the
     *JavaScript signals.
     * @param parentWidget a QWidget instance.
     */
    void setParentWidget(QWidget* parentWidget);

    /**
     * @brief showWindow Delegates the action to show() method of parent widget.
     */
    Q_INVOKABLE void showWindow();
    
};

#endif // JSCRIPTSIGNALHANDLER_H

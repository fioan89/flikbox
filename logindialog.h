#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QString>
#include <QUrl>

#include "jscriptsignalhandler.h"
#include "requesttoken.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit LoginDialog(QWidget *parent = 0, RequestToken* requestToken = 0);
    /**
     * @brief setUserName Sets username for Flickr login page.
     * @param username a string representing the desired username.
     */
    void setUserName(QString username);
    /**
     * @brief setPassword Sets password for Flickr login page.
     * @param password a string representing the desired password.
     */
    void setPassword(QString password);

    /**
     * @brief loadUrl Loads the login page usinge the specified username and password.
     * @param url pointer to the login page.
     */
    void loadUrl(QUrl url);
    ~LoginDialog();
    
private:
    Ui::LoginDialog *ui;
    QString username;
    QString password;
    JScriptSignalHandler* jsHandler;
    RequestToken* requestToken;
private slots:
    /**
     * @brief pageLoadFinished Injects javascript code in the web page when URL finished to load.
     * @param finished true if page successful loaded, false otherwise.
     */\
    void pageLoadFinished(bool finished);
    /**
     * @brief authUrlChanged Executes logic when a URL has been changed.
     * @param url the new URL
     */
    void authUrlChanged(QUrl url);
    /**
     * @brief windowObjectCleared Executes logic when a new page is loaded.
     */
    void windowObjectCleared();
};

#endif // LOGINDIALOG_H

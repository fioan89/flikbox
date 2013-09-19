#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit LoginDialog(QWidget *parent = 0);
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

    /**
     * @brief getLoginScript Builds a javascript to be injected in the login page.
     * @return the javascript file.
     */
    QString getLoginScript();
};

#endif // LOGINDIALOG_H

#include <QVariant>
#include <QWebFrame>
#include "logindialog.h"
#include "ui_logindialog.h"


LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    this->username = "";
    this->password = "";
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::loadUrl(QUrl url)
{
    ui->webView->setUrl(url);
    ui->webView->page()->mainFrame()->evaluateJavaScript(this->getLoginScript());
}

void LoginDialog::setUserName(QString username)
{
    this->username = username;
}

void LoginDialog::setPassword(QString password)
{
    this->password = password;
}

QString LoginDialog::getLoginScript()
{
    QString script = "if(window.location.href.indexOf('login.yahoo.com') > -1) { var userName =  document.getElementById('username');";
            script += "var passWord =  document.getElementById('passwd'); if (typeof(userName) != 'undefined' && userName != null) {";
            script += "userName.value=";
            script += this->username;
            script += "} if (typeof(passWord) != 'undefined' && passWord != null) { passWord.value=";
            script += this->username;
            script += "} }";
    return script;
}

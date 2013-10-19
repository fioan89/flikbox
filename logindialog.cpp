#include <QVariant>
#include <QWebFrame>
#include "logindialog.h"
#include "ui_logindialog.h"


LoginDialog::LoginDialog(QWidget *parent, RequestToken* requestToken) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->username = "''";
    this->password = "''";
    this->jsHandler = new JScriptSignalHandler(this);
    this->jsHandler->setParentWidget((QWidget*) this);
    this->requestToken = requestToken;
}

LoginDialog::~LoginDialog()
{
    delete jsHandler;
    delete ui;
}

void LoginDialog::loadUrl(QUrl url)
{
    this->ui->webView->setUrl(url);
    QObject::connect(this->ui->webView, SIGNAL(loadFinished(bool)), this, SLOT(pageLoadFinished(bool)));
    QObject::connect(this->ui->webView, SIGNAL(urlChanged(QUrl)), this, SLOT(authUrlChanged(QUrl)));
    QObject::connect(this->ui->webView->page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()), this, SLOT(windowObjectCleared()));
}

void LoginDialog::setUserName(QString username)
{
    this->username = username;
}

void LoginDialog::setPassword(QString password)
{
    this->password = password;
}

void LoginDialog::pageLoadFinished(bool finished)
{
    QString script;
    if (finished)
    {
        script = "function showLoginWindow() {\n";
        script += "showWindowObject.showWindow()\n";
        script +="}\n";

        script += "if(window.location.href.indexOf('login.yahoo.com') > -1) {\n";
        script += "var userName =  document.getElementById('username');\n";
        script += "var passWord =  document.getElementById('passwd');\n";
        script += "var buttonLogin = document.getElementById('.save');\n";

        script += "if (typeof(userName) != 'undefined' && userName != null) {\n";
        script += "userName.value='";
        script += this->username + "'";
        script += "\n}\n";

        script += "if (typeof(passWord) != 'undefined' && passWord != null) {\n";\
        script += "passWord.value='";
        script += this->password + "'";
        script += "\n}\n";

        script += "if (typeof(buttonLogin) != 'undefined' && buttonLogin != null) {\n";
        script += "buttonLogin.click()\n";
        script += "}\n";

        script +="\n} else {\n";
        script += "showLoginWindow()\n";
        script += "}\n";
        qDebug("[debug] Page loaded successfully");
    }
    else
    {
        qDebug("[debug] There were problems in loading the page");
    }
    this->ui->webView->page()->mainFrame()->evaluateJavaScript(script);
}

void LoginDialog::authUrlChanged(QUrl url)
{
    QString sUrl = url.toString(QUrl::None);
    if (sUrl.contains("none?oauth_token=", Qt::CaseInsensitive) && sUrl.contains("&oauth_verifier=", Qt::CaseInsensitive))
    {
        qDebug("[debug] Got access, going to close the window");
        QString tokenKey = "oauth_token=";
        QString verifierKey = "&oauth_verifier=";

        int firstIndex = sUrl.indexOf(tokenKey) + tokenKey.length();
        int firstLength = sUrl.indexOf(verifierKey) - firstIndex;
        int secondIndex = sUrl.indexOf(verifierKey) + verifierKey.length();
        int secondLength = sUrl.length() - secondIndex;
        this->requestToken->setOAuthToken(sUrl.mid(firstIndex, firstLength));
        this->requestToken->setOAuthVerifier(sUrl.mid(secondIndex, secondLength));
        this->close();
    }
    else if (sUrl == "http://www.flickr.com/")
    {
        qDebug("[debug] Access refused, going to close the window");
        this->close();
        // TODO - warn user that no further actions can be made until
        // he give us access.
    }
}

void LoginDialog::windowObjectCleared()
{
    this->ui->webView->page()->mainFrame()->addToJavaScriptWindowObject("showWindowObject", this->jsHandler);
}

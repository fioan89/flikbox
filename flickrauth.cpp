#include <ctime>
#include <cstdlib>
#include <QChar>
#include <QEventLoop>
#include <QNetworkRequest>
#include <QPixmap>
#include <QSplashScreen>

#include "accesstoken.h"
#include "crypto.h"
#include "flickrauth.h"
#include "httpmanager.h"

FlickrAuth::FlickrAuth(QWidget* parent, QString userName, QString userPassword, bool rememberMe)
    : QObject(0)
{
    // init block
    this->parent = parent;
    this->userName = userName;
    this->userPassword = userPassword;
    this->rememberMe = rememberMe;
    this->appKey = "9b056c64eb70d14a1fd999393db186fe";
    this->secretKey = "4f72239681847041";

    this->httpManager = HTTPManager::getInstance().getNetworkAccessManager();

    // init random
    Crypto::getRandomString(8);
    // start authentication
    QUrl toRequest = this->getRequestTokenUrl();
    QString oauthTokenHeader = this->getRequestTokenHeader(toRequest);
    qDebug(oauthTokenHeader.toStdString().c_str());
    if (!oauthTokenHeader.contains("oauth_problem"))
    {
        QString oauthToken = this->extractOAuthToken(oauthTokenHeader);
        QString oauthTokenSecret = this->extractOAuthTokenSecret(oauthTokenHeader);
        if (oauthToken != "" && oauthTokenSecret != "")
        {
            RequestToken reqToken = this->authorizeApplicationAccess(oauthToken);
            if ("" != reqToken.getOAuthToken() && "" != reqToken.getOAuthVerifier())
            {
                //AccessToken accessToken = getAccessToken(reqToken);
            }
            else
            {
                // TODO
            }

        }
        else
        {
            // TODO
        }
    }
    else
    {
        // TODO
    }

}

QUrl FlickrAuth::getRequestTokenUrl()
{
    QString nonce = Crypto::getRandomString(8);
    QString timestamp = QString::number(time(0));

    QString requestString[8];
    requestString[0] = "http://www.flickr.com/services/oauth/request_token";
    requestString[1] = "oauth_nonce=" + nonce;
    requestString[2] = "&oauth_timestamp=" + timestamp;
    requestString[3] = "&oauth_consumer_key=" + this->appKey;
    requestString[4] = "oauth_callback=none";
    requestString[5] = "&oauth_signature_method=HMAC-SHA1";
    requestString[6] = "&oauth_version=1.0";

    QString parameters = requestString[4] + requestString[3] + "&" + requestString[1] + requestString[5] + requestString[2] + requestString[6];
    parameters = QUrl::toPercentEncoding(parameters).constData();


    QString baseString = "GET&";
    baseString += QUrl::toPercentEncoding(requestString[0]).constData();
    baseString += "&" + parameters;
    QString keyForHmac = this->secretKey + "&";

    requestString[7] = "&oauth_signature=";
    QString signature;
    bool isValid = false;
    while (!isValid) {
        signature = QString(QUrl::toPercentEncoding(Crypto::toHmacSha1(baseString.toLocal8Bit(), keyForHmac.toLocal8Bit())).constData());
        // I've noticed that toHmacSha1 sometimes returns a signature that contains 0.0000 string
        // and every request that contains signature with this string is not valid.
        if (!signature.contains("0.00"))
        {
            isValid = true;
            continue;
        }
        qDebug("[ Warning ] Signature invalid! Trying to encode again!");
    }
    requestString[7] += signature;

    QString finalReq = requestString[0] + "?" + requestString[1] + requestString[2] + requestString[3] + requestString[5] + requestString[6] +
            requestString[7] + "&" + requestString[4];

    return QUrl(finalReq);
}

QString FlickrAuth::getRequestTokenHeader(QUrl url)
{
    QEventLoop loop;
    connect(httpManager, SIGNAL(finished(QNetworkReply*)), &loop, SLOT(quit()));
    QNetworkReply* reply = httpManager->get(QNetworkRequest(url));
    loop.exec();
    reply->deleteLater();
    return reply->readAll();
}

QString FlickrAuth::extractOAuthToken(QString message)
{
    QString toReturn;
    if (message.contains("oauth_token="))
    {
        QString toSearch=("oauth_token=");
        QString separator("&");
        int startingPosition = message.indexOf(toSearch) + toSearch.length();
        int length = message.indexOf(separator, startingPosition) - startingPosition;
        toReturn = message.mid(startingPosition, length);
    }
    return toReturn;
}


QString FlickrAuth::extractOAuthTokenSecret(QString message)
{
    QString toReturn;
    if (message.contains("oauth_token_secret="))
    {
        QString toSearch=("oauth_token_secret=");
        int startingPosition = message.indexOf(toSearch) + toSearch.length();
        int length = message.length() - startingPosition;
        toReturn = message.mid(startingPosition, length);
    }
    return toReturn;
}


RequestToken FlickrAuth::authorizeApplicationAccess(QString oauth_token)
{
    QUrl url("http://www.flickr.com/services/oauth/authorize?oauth_token=" + oauth_token + "&perms=delete");
    RequestToken requestToken;

    qDebug(url.toString().toStdString().c_str());
    if (this->loginDialog == NULL)
    {
        this->loginDialog = new LoginDialog(this->parent, &requestToken);
    }
    QEventLoop loop;
    loop.connect(this->loginDialog, SIGNAL(destroyed(QObject*)), SLOT(quit()));

    QPixmap pixmap(":/icons/icons/flickbox_loading_splash_46x46.gif");
    QSplashScreen *splash = new QSplashScreen(pixmap);

    splash->show();
    this->loginDialog->setUserName(this->userName);
    this->loginDialog->setPassword(this->userPassword);
    this->loginDialog->loadUrl(url);
    loop.exec();
    delete splash;
    return requestToken;
}

AccessToken FlickrAuth::getAccessToken(RequestToken requestToken)
{
    QUrl toCall("http://www.flickr.com/services/oauth/access_token?oauth_nonce=" + Crypto::getRandomString(8) +
                "&oauth_timestamp=" + QString::number(time(0)) + "&oauth_verifier=" + requestToken.getOAuthVerifier() +
                "&oauth_consumer_key=" + this->appKey + "&oauth_signature_method=HMAC-SHA1&oauth_version=1.0&oauth_token=" +
                requestToken.getOAuthToken() + "&oauth_signature=");
}

FlickrAuth::~FlickrAuth()
{
    if (this->loginDialog != NULL)
    {
        delete this->loginDialog;
    }
}

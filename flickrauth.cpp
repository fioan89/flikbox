#include <ctime>
#include <cstdlib>
#include <QChar>
#include <QEventLoop>
#include <QNetworkRequest>

#include "crypto.h"
#include "flickrauth.h"
#include "httpmanager.h"

FlickrAuth::FlickrAuth(QString userName, QString userPassword, bool rememberMe)
    : QObject(0)
{
    // init block
    this->userName = userName;
    this->userPassword = userPassword;
    this->rememberMe = rememberMe;
    this->appKey = "9b056c64eb70d14a1fd999393db186fe";
    this->secretKey = "4f72239681847041";
    this->tokenSeriveHasReplied = false;

    this->httpManager = HTTPManager::getInstance().getNetworkAccessManager();

    // init random
    Crypto::getRandomString(8);
    // start authentication
    QUrl toRequest = this->getRequestTokenUrl();
    QString oauthTokenHeader = this->getRequestTokenHeader(toRequest);
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
    return reply->readAll();
}


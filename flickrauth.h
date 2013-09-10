#ifndef FLICKRAUTH_H
#define FLICKRAUTH_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QString>
#include <QUrl>

class FlickrAuth : public QObject
{
    Q_OBJECT
private:
    QString appKey;
    QString secretKey;
    QString userName;
    QString userPassword;
    bool rememberMe;
    volatile bool tokenSeriveHasReplied;

    QNetworkAccessManager* httpManager;

    /**
     * @brief getRequestTokenUrl Gets an url that can be used to request a token from
     * Flickr auth service.
     * @return a QUrl
     */
    QUrl getRequestTokenUrl();

    /**
     * @brief getRequestTokenHeader Gets Flickr page containing the oauth_token and
     * oauth_token_secret. The page is returned as a single string. If the page cannot
     * be retrieved an empty string is returned.
     * @param url Flickr url that points to a request token page.
     * @return a string containing the oauth_token and oaut_token_secret.
     */
    QString getRequestTokenHeader(QUrl url);

public:
    FlickrAuth(QString userName, QString userPassword, bool rememberMe);

};

#endif // FLICKRAUTH_H

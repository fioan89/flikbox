#ifndef FLICKRAUTH_H
#define FLICKRAUTH_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QString>
#include <QUrl>

#include "logindialog.h"

class FlickrAuth : public QObject
{
    Q_OBJECT
private:
    QString appKey;
    QString secretKey;
    QString userName;
    QString userPassword;
    bool rememberMe;
    QWidget* parent;
    LoginDialog* loginDialog;

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

    /**
     * @brief extractOAuthToken Finds the oauth_token key in the given
     * message returns its value.
     * @param message a string containing an oauth_token and it's value separated by "=" char.
     * @return the oauth_token value or an empty string if the key could not be found.
     */
    QString extractOAuthToken(QString message);

    /**
     * @brief extractOAuthTokenSecret Finds the oauth_token_seccret key in the given
     * message returns its value.
     * @param message a string containing an oauth_token_secret and it's value separated by "=" char.
     * @return the oauth_token_secret value or an empty string if the key could not be found.
     */
    QString extractOAuthTokenSecret(QString message);

    bool authorizeApplicationAccess(QString oauth_token);

public:
    FlickrAuth(QWidget* parent, QString userName, QString userPassword, bool rememberMe);

    ~FlickrAuth();
};

#endif // FLICKRAUTH_H
